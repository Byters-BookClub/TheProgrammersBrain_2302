import { Request, Response, NextFunction } from 'express';

// 미들웨어.. 뭐 하는 계층이지??
// 공통적으로 이렇게 쓰겠다를 설정해주는 건가??
export type Middleware = (
  req: Request,
  res: Response,
  next: NextFunction,
) => void;
