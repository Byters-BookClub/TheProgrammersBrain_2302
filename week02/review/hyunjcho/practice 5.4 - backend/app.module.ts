import {
  CacheModule,
  MiddlewareConsumer,
  Module,
  NestModule,
} from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { AuthModule } from './auth/auth.module';
import configuration from './config/configuration';
import { SessionMiddleware } from './middleware/session-middleware';
import { join } from 'path';
import { BlackholeModule } from './blackhole/blackhole.module';
import { ServeStaticModule } from '@nestjs/serve-static';
import { TypeOrmModule } from '@nestjs/typeorm';
import TypeOrmConfigService from './config/typeorm.config';
import { DataSource } from 'typeorm';
import { addTransactionalDataSource } from 'typeorm-transactional';
import { CabinetModule } from './cabinet/cabinet.module';
import { LentModule } from './lent/lent.module';
import { UserModule } from './user/user.module';
import { UtilsModule } from './utils/utils.module';
import { EventEmitterModule } from '@nestjs/event-emitter';
import { BetatestModule } from './betatest/betatest.module';
import { AdminModule } from './admin/admin.module';

@Module({ // 스프링에서는 딱히 메인의 존재가 크지 않고 단순히 어플리케이션을 구동시키는 정도이고 나머지는 프론트에서 호출하는 부분에 따라 해당 컨트롤러에서 시작하는데 여기는 앱 모듈에 모든 것들이 임포트 돼있어서 생소하다
  // 여기서 전반적인 설정을 해주는 건가 싶기도?
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
