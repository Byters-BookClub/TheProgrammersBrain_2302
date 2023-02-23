/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:50:10 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "executor_internal.h"

int	io_manager(int mode)
// 함수 이름대로 입출력 (input/output)을 관리(manage)하는 것 같다.
// 근데 redirection도 결국 표준입출력 설정이기 때문에 redir 처리를 하는 함수와 io_manager가 조금 헷갈리게 느껴지기도 한다.
{
	static int	backup[2];	// 인덱스 0이 IN, 1이 OUT의 backup인가보군.
							// 이것도 매크로 상수로 두었으면 좋았을 것 같기도? (하지만 지금도 읽는데는 문제 없음. 오히려 없는게 더 깔끔한 것 같기도하고?)

	if (mode == STDINOUT_BACKUP)
	{
		backup[0] = dup(STDIN_FILENO);
		backup[1] = dup(STDOUT_FILENO);
		if (backup[0] < 0 || backup[1] < 0)
		{
			ft_dprintf(2, "%scritical I/O error: cannot redirect STDIN/OUT\n",
				MSG_ERROR_PREFIX);
			return (CODE_ERROR_IO);
		}
	}
	else if (mode == STDINOUT_RESTORE)
	{
		if (dup2(backup[0], STDIN_FILENO) < 0 || close(backup[0]) < 0
			|| dup2(backup[1], STDOUT_FILENO) < 0 || close(backup[1]) < 0)
		{
			ft_dprintf(2, "%scritical I/O error: cannot redirect STDIN/OUT\n",
				MSG_ERROR_PREFIX);
			return (CODE_ERROR_IO);
		}
	}
	return (CODE_OK);
}
