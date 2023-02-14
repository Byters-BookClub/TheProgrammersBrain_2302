import { Inject, Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import * as cookieParser from 'cookie-parser';
import { Middleware } from './middleware';

@Injectable()
export class SessionMiddleware {        // 미들웨어 개념이 없어서 이부분이 가장 이해가 안 되는 부분임. 간단히 정의를 찾아봤을 땐 각 기능들을 연결해주는 객체처럼 설명이 돼 있는데 세션 미들웨어? 세션은 쿠키, 이용자에 대한 관리를 나타내는데, 그러면 세션으로 관리한다는 것이 각 기능들을 연결해준다는 의미인건가?
  cookieParser: Middleware;
  helmet: Middleware;

  constructor(@Inject(ConfigService) private configService: ConfigService) {
    this.cookieParser = cookieParser();
    // this.helmet = helmet({
    //   contentSecurityPolicy: {
    //     directives: {
    //       defaultSrc: ["'self'"],
    //       scriptSrc: ["'self'", configService.get<string>('fe_host')],
    //       styleSrc: ["'self'", configService.get<string>('fe_host')],
    //       imgSrc: ["'self'", configService.get<string>('fe_host')],
    //       fontSrc: ["'self'", configService.get<string>('fe_host')],
    //       connectSrc: ["'self'", configService.get<string>('fe_host')],
    //       objectSrc: ["'none'"],
    //       upgradeInsecureRequests: [],
    //     },
    //   },
    // });
  }
}
