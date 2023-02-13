import {
  CacheModule,
  MiddlewareConsumer,
  Module,
  NestModule,
} from '@nestjs/common';  // 여러 개를 import할 때는 한 줄에 하나씩 하도록 convention이 설정되어있나보구나...
import { ConfigModule, ConfigService } from '@nestjs/config';

/**
 * 우아악~~~~~~~backend 디렉토리 내에서 디렉토리로 나눠둔 각 기능들을 여기서 다 import하네.
 * 아무래도 이 app.module가 backend의 중심과 같은 역할인 것 같다! 
 * main보다 오히려 이 녀석을 더 면밀히 살펴보아야할 듯...
 */

import { AuthModule } from './auth/auth.module'; 
// 인증 관련 모듈.

import configuration from './config/configuration';
// 환경변수 파일 '.env'로 부터 갖고 온 설정(configuration) 관련 값들을 갖고있는 객체인 것 같다.

import { SessionMiddleware } from './middleware/session-middleware';
// 세션 관련 미들웨어. (근데 뭘 하는지는 잘 모르겠다.)

import { join } from 'path'; // 이게 뭐지?

import { BlackholeModule } from './backend_code/blackhole/blackhole.module';
// 블랙홀 모듈.

import { ServeStaticModule } from '@nestjs/serve-static'; // 이게 뭐지??

// orm이라고 써있는 것을 보니 데이터베이스 관련인 것 같다. sql도 orm에 속했었나, 무튼 sql이 들어가 있는 것을 보면 확실한 듯.
import { TypeOrmModule } from '@nestjs/typeorm';
import TypeOrmConfigService from './config/typeorm.config'; // 데이터베이스 설정.
import { DataSource } from 'typeorm';
import { addTransactionalDataSource } from 'typeorm-transactional';


import { CabinetModule } from './cabinet/cabinet.module';
// 캐비넷 모듈. cabinet42니까....이게 핵심 기능인가?
  // 읽어보니 데이터베이스로부터 캐비넷에 대한 정보(위치, 대여자 등)을 갖고오는 모듈인 것 같다.

import { LentModule } from './lent/lent.module';
// 대여(lent) 관련 모듈. 캐비넷 모듈에 lent 기능은 포함되어있지 않나보다.
  // 캐비넷의 대여, 반납, 메모 기능을 수행하고 있다. 

import { UserModule } from './user/user.module';
// 유저 모듈. 유저를 관리하는 모듈?
  // 읽어보니 특정 유저 개인에 대해서 정보를 얻어오거나 유저 리스트를 조회 및 관리(삭제)하는 모듈인듯
  // 포괄적으로 user module이라 이름 붙인 것 같다.

import { UtilsModule } from './utils/utils.module';
// 만료일자확인, 날짜계산, 이메일 전송, 스케줄링 등 잡다한 유틸들.

import { EventEmitterModule } from '@nestjs/event-emitter'; // 이게 뭐지? 이벤트?
import { BetatestModule } from './betatest/betatest.module'; // 베타 테스트에서 쓰는 모듈.
import { AdminModule } from './admin/admin.module'; // 관리자(administrator)에게 필요한 모듈인듯

@Module({
  imports: [
    ConfigModule.forRoot({
      load: [configuration],
      isGlobal: true, // TODO: remove after
    }),
    TypeOrmModule.forRootAsync({
      imports: [ConfigModule],
      useClass: TypeOrmConfigService,
      async dataSourceFactory(options) {
        if (!options) {
          throw new Error('No options');
        }
        return addTransactionalDataSource(new DataSource(options));
      },
    }),
    AdminModule,
    AuthModule,
    BlackholeModule,
    EventEmitterModule.forRoot(),
    CabinetModule,
    LentModule,
    UserModule,
    UtilsModule,
    CacheModule.register({
      isGlobal: true,
    }),
    ...(process.env.LOCAL === 'true'
      ? [
          ServeStaticModule.forRootAsync({
            inject: [ConfigService],
            useFactory: () => [
              {
                rootPath: join(__dirname, '../', 'deploy'),
                exclude: ['/api/(.*)', '/auth/(.*)'],
              },
            ],
          }),
        ]
      : []),
    // import if UNBAN_API=true
    ...(process.env.UNBAN_API === 'true' ? [BetatestModule] : []),
  ],
  controllers: [],
  providers: [SessionMiddleware],
})
export class AppModule implements NestModule {
  constructor(public sessionMiddleware: SessionMiddleware) {}

  configure(consumer: MiddlewareConsumer) {
    // NOTE: JWT 토큰이 쿠키에 저장되기 때문에 모든 경로에 대해 해당 미들웨어 적용
    consumer
      .apply(this.sessionMiddleware.cookieParser, this.sessionMiddleware.helmet)
      .forRoutes('*');
  }
}
