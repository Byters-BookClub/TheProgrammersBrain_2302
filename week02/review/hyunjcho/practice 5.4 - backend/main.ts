import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { SwaggerModule, DocumentBuilder } from '@nestjs/swagger';
import { ConfigService } from '@nestjs/config';
import { initializeTransactionalContext } from 'typeorm-transactional';
import { LogLevel } from '@nestjs/common';

async function bootstrap() {
  initializeTransactionalContext();
  const log_level: LogLevel[] =
    process.env.DEBUG_LOG === 'false'
      ? ['error', 'log']
      : ['error', 'log', 'debug'];
  const app = await NestFactory.create(AppModule, {
    logger: log_level,
  });
  // for URI Versioning
  app.enableVersioning();
  const swaggerConfig = new DocumentBuilder() // swagger 문서 작성
    .setTitle('Cabi API')
    .setDescription('Cabi API 명세')
    .setVersion('4.0')
    .addBearerAuth()
    .build();
  const swaggerDocument = SwaggerModule.createDocument(app, swaggerConfig);
  SwaggerModule.setup('docs', app, swaggerDocument);
  const configService = app.get(ConfigService);
  const port = configService.get<number>('port'); // 포트를 지정해 주는 일이 있네. 프론트 연동 때문인가? 8080도 지정을 해주던가? 스프링에서 어떻게 했더라...
  app.enableCors({
    origin: process.env.FE_HOST,
    methods: 'GET,HEAD,PUT,PATCH,POST,DELETE,OPTIONS',
    credentials: true,
  });
  await app.listen(port); // 이걸 통해서 요청을 실행하는 듯...?
}
bootstrap(); // 서버 실행 시에 여기가 가장 먼저 실행 되는 건가?
