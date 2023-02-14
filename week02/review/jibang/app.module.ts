import {
  CacheModule,
  MiddlewareConsumer,
  Module,
  NestModule,
} from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { AuthModule } from './auth/auth.module';            // 당연히 인증 기능이겠지
import configuration from './config/configuration';         // 어떤 설정?
import { SessionMiddleware } from './middleware/session-middleware'; // 미들웨어는 찾아보니 각 기능들을 연결시켜주는 객체 정도로 이해가 됨
import { join } from 'path';
import { BlackholeModule } from './blackhole/blackhole.module'; // 블랙홀에 빠지면 못쓰게 하는 그런 기능인가?
import { ServeStaticModule } from '@nestjs/serve-static';   // 이거는 static 페이지를 보여주는 모듈인듯
import { TypeOrmModule } from '@nestjs/typeorm';          // ??
import TypeOrmConfigService from './config/typeorm.config'; // ??
import { DataSource } from 'typeorm';
import { addTransactionalDataSource } from 'typeorm-transactional'; // ??
import { CabinetModule } from './cabinet/cabinet.module';   // 캐비넷을 대여시켜주는 애?인줄 알았는데 밑에 lent가 있는 걸 보니까 전반적인 관리를 하는 모듈인가.
import { LentModule } from './lent/lent.module';  // lent라고 한 것으로 보아 lend .. 빌려주는 애..?
import { UserModule } from './user/user.module';  // 현재 사물함을 대여하고 있는 사용자에 대한 모듈? 아니면 전체 가입자?
import { UtilsModule } from './utils/utils.module'; // 각 모듈에서 사용되는 유틸 함수들이겄지
import { EventEmitterModule } from '@nestjs/event-emitter'; // ??
import { BetatestModule } from './betatest/betatest.module'; // 베타테스트
import { AdminModule } from './admin/admin.module'; // 관리자 권한의 어떤 모듈.. 통계나 이런걸 볼수가 있나?

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
    AdminModule,            // 이부분에서 전체 모듈을 실제 사용하는 부분인듯..
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
