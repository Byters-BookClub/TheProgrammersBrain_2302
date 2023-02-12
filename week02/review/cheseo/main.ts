// 뭔가 여기는 외부 라이브러리를 이런 이름으로 들고와라 하는 거겠지
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { SwaggerModule, DocumentBuilder } from '@nestjs/swagger';
import { ConfigService } from '@nestjs/config';
import { initializeTransactionalContext } from 'typeorm-transactional';
import { LogLevel } from '@nestjs/common';

// ts이다보니 js랑 느낌이 비슷하네
/*
	bootstrap이 main인 듯
	bootstrap의 뜻이 뭘까?
		원래 bootstrap은 부츠 뒷쪽의 작은 고리로, 부츠는 신기 어려워니 신는 것을 도와주는 고리를 뜻했다. 이게 "pull oneself up by one's bootstraps", 스스로 자신의 상황을 개선시킨다는 관용구가 생김.
		이것이 훗날 컴퓨터공학에 쓰이며, bootstrap, 즉 줄여서 부팅이라는 용어로 변했다.
	여기서 왜 main이라는 함수로 쓰이지 않고 왜 bootstrap이라는 용어를 썼나 했더니 bootstrap이 부팅이라는 의미가 있다면 납득이 간다.
*/
async function bootstrap() {
  // 부팅에 필요한 context들을 초기화 하는 함수
  initializeTransactionalContext();
  // 로그 메세지 남기는데 필요한 배열인듯. 로그가 저 배열 안에 채워지는 것 같다
  const log_level: LogLevel[] =
    // process라는게 뭘까?
    process.env.DEBUG_LOG === 'false'
      ? ['error', 'log']
      : ['error', 'log', 'debug'];
  // i don't get what this app means
  const app = await NestFactory.create(AppModule, {
    logger: log_level,
  });
  // for URI Versioning
  app.enableVersioning();
  // swagger이라는 프레임워크가 있다네. config라는 걸 보니 초기 설정을 여기서 하나보다.
  const swaggerConfig = new DocumentBuilder()
    .setTitle('Cabi API')
    .setDescription('Cabi API 명세')
    .setVersion('4.0')
    .addBearerAuth()
    .build();
  // document? 랜더링하는데 필요한 문서(?)인가
  const swaggerDocument = SwaggerModule.createDocument(app, swaggerConfig);
  SwaggerModule.setup('docs', app, swaggerDocument);
  const configService = app.get(ConfigService);
  const port = configService.get<number>('port');
  app.enableCors({
    origin: process.env.FE_HOST,
    methods: 'GET,HEAD,PUT,PATCH,POST,DELETE,OPTIONS',
    credentials: true,
  });
  // app이 port랑 이런 거 설정하는 것보니까 서버랑 소통해서 페이지를 들고오나보다
  await app.listen(port);
}

// bootstrap이라는 큰 main함수가 필요한 모든 것을 실행하는 구조인듯 => 서비스를 부팅하는 함수
bootstrap();

/*
  1. 여기서는 일단 모든 변수(context)를 초기화하고,
  2. 로그 메세지를 남길 수 있게 debug log를 설정하고,
  3. app을 생성, swagger라는 프레임워크를 사용해서 RESTful api 문서를 구셩해주는 프레임워크를 사용하여 api랑 소통하고
  4. 포트를 사용해서 서버랑 연결하나보다

  아쉬운 점: app이라는 것이 뭔지, ts문법이 많이 낯설어서 정확이 무슨 일을 하는 함수인지 알 수 없어서 아쉽다. 아는 것이 없어 모르는 부분은 상상과 예측으로 때워야하는게 조금 아쉽다. 내가 이렇게 예측한 것이 맞는지 확인할 방법이 있으면 좋겠다.
*/