import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { SwaggerModule, DocumentBuilder } from '@nestjs/swagger';
import { ConfigService } from '@nestjs/config';
import { initializeTransactionalContext } from 'typeorm-transactional';
import { LogLevel } from '@nestjs/common';
// 필요한 모듈들을 import


async function bootstrap() {
  initializeTransactionalContext();			// transaction context? 추측으로는 사물함 관련 예약 서비스니까 각종 변수들을 초기화하는 것으로 처음 예상은 그랬는데.. 모듈에서 import한 것으로 보아 뭔가 사물함 예약 내역을 기록해주는 모듈을 사용할때 초기화해주는 함수 같음
  const log_level: LogLevel[] =
    process.env.DEBUG_LOG === 'false'		// 디버그 로그라고 돼 있는거 보니 유지보수할고 만든 변수인듯
      ? ['error', 'log']
      : ['error', 'log', 'debug'];
  const app = await NestFactory.create(AppModule, { // NestFactory? nestjs를 잘 몰라서 찾아봤는데 대강 클라와 서버 사이에서 요청을 해주고 그런 모듈인듯. 이를 app으로 선언해서 내장함수를 사용하는 것 같다.
    logger: log_level,
  });
  // for URI Versioning
  app.enableVersioning();
  const swaggerConfig = new DocumentBuilder()
    .setTitle('Cabi API')
    .setDescription('Cabi API 명세')
    .setVersion('4.0')
    .addBearerAuth()
    .build();
  const swaggerDocument = SwaggerModule.createDocument(app, swaggerConfig); // 이부분까지 읽다가 도저히 이해가 안 돼 찾아봤는데... https://docs.nestjs.com/openapi/introduction  nestjs에 대한 디자인 패턴과 비슷한 구조로 돼 있는 것을 알 수 있었음
  SwaggerModule.setup('docs', app, swaggerDocument);
  const configService = app.get(ConfigService);
  const port = configService.get<number>('port');
  app.enableCors({
    origin: process.env.FE_HOST,
    methods: 'GET,HEAD,PUT,PATCH,POST,DELETE,OPTIONS',
    credentials: true,
  });
  await app.listen(port);	// listen과 port가 나온 것으로 보아 main.ts는 서버를 구동시키는 백엔드 코드라는 것을 상기하게 됐음. 그렇다면.. bootstrap()내에 각종 기능들을 포함하는 함수가 있을 것임. 그건 뭘까? 아마 app.module.ts라는 파일이 같은 디렉터리내 존재하고, 여기서 다른 소스들을 인클루드 하고 있는 것으로 보아 app 객체를 만들때 포함시켜준 것으로 추측됨.
}
bootstrap(); // focus가 되는 함수로 보임. 그런데 bootstrap이 도대체 뭘 하는 함수일까? bootstrap은 그거 아닌가..css같이 홈피 꾸며주는..
