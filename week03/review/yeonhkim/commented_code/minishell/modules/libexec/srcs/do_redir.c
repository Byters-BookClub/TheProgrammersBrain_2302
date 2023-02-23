/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:49:56 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "heredoc.h"
#include "msgdef.h"
#include "executor_internal.h"

// process_redir가 내부적으로 do_redir로 시작하는 같은 소스 파일 내 다른 함수들을 호출하고 있고,
// 그래서 외부에서는 process_redir만 호출되고 있는 듯 하다.
// 외부에서 호출되지 않는 함수들은 static으로 적절히 감춰두고 파일명 또한 process_redir로 해두었으면 좋았을 것 같다.
int	process_redir(t_redir *redir_arr, int n_redir)
{
	const t_do_redir	do_redir[5] = {
	[REDIR_NONE] = 0, [REDIR_IN] = do_redir_in, [REDIR_OUT] = do_redir_out,
	[REDIR_IN_HERE] = do_redir_in_here, [REDIR_OUT_APPEND] = do_redir_out_append
	};
	// 줄 수가 문제되지 않는다면 한 line마다 하나의 요소를 선언해두는 것이 가독성이 더 좋았을 것 같다.
	// REDIR_NONE일때는 해당하는 함수를 호출하지 않는 모양인데, 그러면 사실 요소로 둘 필요가 없다. (애초에 do_redir 배열에 접근하지 않기 때문에)
		// 그리고 두더라도 값을 NULL로 주는 것이 좋았을 것 같다. 왜냐하면 t_do_redir는 함수 포인터 타입이기 때문에.
	int					i;

	i = -1; // 줄 수가 부족한 것도 아닌데 -1부터 시작하게 할 필요는 없을 것 같다.
	while (++i < n_redir)
	{
		if (redir_arr[i].type == REDIR_NONE)
		{
			ft_dprintf(2, "critical error: redir type is none\n");	// redir 타입이 none일 수가 있나보구나. 어떤 경우인지 궁금하다.
			continue ; // 음? REDIR_NONE일 경우 critical error가 발생한 것으로 간주하는데 왜 continue하는거지????
						// 상식적으로는 break ;하고 이 커맨드의 실행을 멈췄어야 했을 것 같은데.......
		}
		if (do_redir[redir_arr[i].type](redir_arr + i) != CODE_OK)
			return (CODE_ERROR_IO);
	}
	return (CODE_OK);
}

/**
 * do_redir_ 함수들에 대한 의견: 
 * 		1. redirection의 type을 판별해서 함수를 호출하고 있기 때문에
 * 		t_redir 포인터가 아니라 멤버인 content만 넘겼어도 되었을 것 같다.
 * 		2. process_redir에서만 호출하고 있으므로 static 함수로 두는 편이 더 좋았을 것 같다.
 */

int	do_redir_in(t_redir *redir_arr)
	// 음???? redir_arr의 한 요소만 전달받는데 대체 왜 파라미터 명이 redir_arr지?
	// 그냥 'redir'로 하는 것이 더 좋았을 것 같다.
{
	int	fd;

	if (access(redir_arr->content, F_OK) != 0)
	{
		ft_dprintf(2, "%s%s: No such file or directory\n",
			MSG_ERROR_PREFIX, redir_arr->content);
		return (CODE_ERROR_IO);
	}
	if (access(redir_arr->content, R_OK) != 0)
	{
		ft_dprintf(2, "%s%s: Permission denied\n",
			MSG_ERROR_PREFIX, redir_arr->content);
		return (CODE_ERROR_IO);
	}
	fd = open(redir_arr->content, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	// 하나의 조건문 안에서 여러 실행의 결과를 한번에 확인하고 있군...
	// 주의를 기울여 읽지 않으면 놓칠 수도 있게 될 것 같긴 하지만, 일견 간결해 보이긴 한다.
	return (CODE_OK);
}

int	do_redir_out(t_redir *redir_arr)
{
	int	fd;

	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	do_redir_in_here(t_redir *redir_arr)
{
	int		fd;
	char	*heredoc_file;

	(void)redir_arr;
	if (heredoc_get_next_filename(&heredoc_file) != CODE_OK)
		return (CODE_ERROR_IO);
	fd = open(heredoc_file, O_RDONLY);
	free(heredoc_file);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

// do_redir_out과 비교했을 때 open 함수를 호출할 시 인자로 O_APPEND가 추가로 있다는 점만 다르고 나머지는 모두 동일하다.
// -> 필요없이 코드가 중복되고 있다.
	// 그래서, 상단에 상수(constant)로 'opt_append = (redir_arr->type == REDIR_OUT_APPEND) * O_APPEND;'
	// 이런 변수로 두고, open시 옵션 인자에 이 변수를 OR 연산해두었으면 두 함수를 하나로 합칠 수 있었을 것 같다.
int	do_redir_out_append(t_redir *redir_arr)
{
	int	fd;

	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}




