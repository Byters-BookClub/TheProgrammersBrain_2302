// 42cabi/backend/src/admin/admin.module.ts

import { Module } from '@nestjs/common';
import { AdminCabinetModule } from 'src/admin/cabinet/cabinet.module';
import { AdminLentModule } from 'src/admin/lent/lent.module';
import { AdminLogModule } from 'src/admin/log/log.module';
import { AdminAuthModule } from 'src/admin/auth/auth.module';
import { AdminReturnModule } from './return/return.module';
import { AdminSearchModule } from './search/search.module';
import { AdminDevelopModule } from 'src/admin/develop/develop.module';
import configuration from 'src/config/configuration';
import { ConfigModule } from '@nestjs/config';

@Module({
  imports: [
    ConfigModule.forRoot({
      load: [configuration],
    }),
    AdminAuthModule,
    AdminLentModule,
    AdminLogModule,
    AdminCabinetModule,
    AdminSearchModule,
    AdminReturnModule,
    ...(process.env.DEV === 'true' ? [AdminDevelopModule] : []),
  ],
  controllers: [],
  providers: [],
})
export class AdminModule {}

/*
  1. 가장 먼저 시선을 끈 코드의 구성 요소 (변수, 클래스, 프로그래밍 개념 등)는 무엇인가?
  - module이 무엇이지?
  2. 왜 그런가?
  - import해서 사용하는 것인가? 그럼 include랑 무슨 차이가 있지?
  3. 두 번째로 주의를 끈 것은 무엇인가?
  - process가 무엇이지?
  4. 왜 그런가?
  - 아까 main.ts에서도 봤는데, 이게 무슨 중요한 역할을 하는 변수인가? 일단 변수이긴 한건가?
  5. 그 두 가지 (변수, 클래스, 프로그래밍 개념 등)는 서로 관련이 있는가?
  - 아마도 관련이 없는 듯...?
  6. 코드에 어떤 개념들이 존재하는가? 그 개념들을 다 알고 있는가?
  - module, import/export
  7. 코드에 어떤 문법 요소들이 존재하는가? 그 문법 요소들을 다 알고 있는가?
  - 문법 요소들 다 몰랑 ts 어려웡
  8. 코드에 어떤 도메인 개념들이 존재하는가? 그것들을 다 알고 있는가?
  - 일단 어디서부터 모르는지 모르는 상태인지라 뭘 공부해야할지 모르겠어요.
*/