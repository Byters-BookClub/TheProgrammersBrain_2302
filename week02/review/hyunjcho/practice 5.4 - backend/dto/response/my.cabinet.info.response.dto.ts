import { ApiPropertyOptional } from '@nestjs/swagger';
import { CabinetExtendDto } from '../cabinet.extend.dto';
import { LentDto } from '../lent.dto';

// 그냥 디티오와 리스폰스, 리퀘스트 디티오가 나뉘어있는데 
/**
 * 내 사물함에 대한 정보 (메모 포함)와 대여한 사람들 정보
 * @extends CabinetExtendDto
 */
export class MyCabinetInfoResponseDto extends CabinetExtendDto {
  @ApiPropertyOptional({
    description: '대여되어 있을 경우 대여 정보',
    type: [LentDto],
  })
  lent_info?: LentDto[]; // 대여한 유저의 정보 (optional)
}
