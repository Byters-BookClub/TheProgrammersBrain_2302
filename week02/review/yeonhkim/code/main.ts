import { NestFactory } from '@nestjs/core';

import { AppModule } from './app.module'; 
// 유일하게 직접 정의해서 import한 객체는 AppModule 하나 뿐인 것 같다.

import { SwaggerModule, DocumentBuilder } from '@nestjs/swagger';
import { ConfigService } from '@nestjs/config';
import { initializeTransactionalContext } from 'typeorm-transactional';
import { LogLevel } from '@nestjs/common';
// 전반적으로 nestjs를 주로 사용하는구나 (swagger는 그 이름만 들어보았는데, 아마 nestjs의 모듈 같다.)

async function bootstrap() {
  initializeTransactionalContext();
  const log_level: LogLevel[] =       // 로그의 레벨을 여기서 정하나보다
    process.env.DEBUG_LOG === 'false'
      ? ['error', 'log']
      : ['error', 'log', 'debug'];      // debug 모드라면 log의 수준이 다른가보군.

  // 직접 정의한 AppModule은 여기서만 쓰이네. NestFactory에서 create 메서드를 사용하기 위해 필요한 인자였던 것 같다.
  const app = await NestFactory.create(AppModule, { 
    logger: log_level,            // 위에서 정한 로그의 레벨 log_level이 app을 create할 때 바로 쓰이네
  });
  // for URI Versioning
  app.enableVersioning();
  const swaggerConfig = new DocumentBuilder()   // swagger 관련 설정을 하나보다. 
    .setTitle('Cabi API')
    .setDescription('Cabi API 명세')
    .setVersion('4.0')
    .addBearerAuth()
    .build();
  const swaggerDocument = SwaggerModule.createDocument(app, swaggerConfig); // 22번 줄의 config를 사용하여 documnet를 정의하는군


  SwaggerModule.setup('docs', app, swaggerDocument);
// app 그리고 swagger 관련 설정 및 도큐먼트 객체를 통해 swagger 모듈을 설정하는군

  const configService = app.get(ConfigService); // '@nestjs/config'로 부터 import한 객체를 통해 객체를 정의하네
  const port = configService.get<number>('port'); // configService에 이미 사용하기로 정해진 포트 넘버가 있나보다.
  app.enableCors({
    origin: process.env.FE_HOST,
    methods: 'GET,HEAD,PUT,PATCH,POST,DELETE,OPTIONS',  // http 프로토콜일까?
    credentials: true,
  });
  await app.listen(port); // 28번 줄에서 지정한 포트 넘버로 listen하는군. 여기서 무한반복하겠지...
}
bootstrap();  // 순간 부트스트랩이 무엇인가 했는데 위에서 정의한 함수구나. main.ts를 실행하면 위에 정의된 함수가 실행된다고 보면 되겠군.
