/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:42:50 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "envmanager.h"
#include "sighandler.h"
#include "strutils.h"
#include "msgdef.h"
#include "executor_internal.h"

static int	set_fd_stream(t_info *info)
// info로 한번에 전달하기 보다는 이 함수에서 필요한 것들만 적절히 넘기는게 좋았을 것 같다.
{
	const t_exec_unit	cur_unit = info->units->arr[info->cur_idx];
	// 아쉽게도 여전히 인자로 현재 처리해야하는 exec_unit의 주소를 넘겨받지 않고
	// 새로 주소를 구하고 있지만, 그래도 const로 해두어서 한결 읽기 낫다.

	if (info->units->n_unit == 1)
		return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));

	if (info->cur_idx == 0)
	{
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (info->cur_idx == info->n_unit - 1)
	{
		if (dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));
}

void	if_dir_then_exit_126(char *cmd_name)
// 아마 norm 때문에 줄 수가 부족해서 따로 빼신 것 같다.
{
	struct stat	s_statbuf;

	if (stat(cmd_name, &s_statbuf) != 0)
	{
		ft_dprintf(2, "%s%s: failed to fetch stat\n",
			MSG_ERROR_PREFIX, cmd_name);
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(s_statbuf.st_mode))
	{
		ft_dprintf(2, "%s%s: is a directory\n", MSG_ERROR_PREFIX, cmd_name);
		exit(126);
	}
}

void	child_exec_extern(t_info *info)
{
	char	**argv;
	int		status;
	char	**envp_paths;

	argv = (info->units->arr + info->cur_idx)->argv; // 앞선 함수 child_exec_cmd에서 argv를 이미 구했는데 그걸 인자로 넘겨받지 않아서 또 구하고 있네???
	status = find_exec(&argv[0]);
	if (status == CODE_ERROR_MALLOC)
		exit(EXIT_FAILURE);
	if (status == CODE_ERROR_GENERIC)	// 대체 무슨 오류인걸까?
		exit(127);
	if (envman_getenvp(&envp_paths) || envman_setval("_", argv[0]))
		exit(EXIT_FAILURE);
	if_dir_then_exit_126(argv[0]);
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp_paths);
	else
	{
		ft_dprintf(2, "%s%s: Permission denied\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
	exit(127);
}

void	child_exec_cmd(t_info *info)
// 이 함수는 반복문 안에서 매 반복마다 호출되는 함수인데,
// 해당 반복 실행에 알맞은 인자가 전달되고 있지 않아 내부에서 불필요하게 주소에 idx(반복 횟수)를 더해 주소를 또 새로 구하고 있다.
	// (이 함수의 지역변수인 unit을 구하는 부분을 볼 것)
// 인자로 현 반복에 알맞는 t_exec_unit의 주소를 전달하는 것이 더 좋았을 것 같다.
{
	t_exec_unit	*unit;
	char		**argv; // unit 변수 내부에 argv 변수가 이미 있는데 왜 굳이 argv 변수가 또 있는거지? unit->argv로 접근하면 되는거 아닌가?
	int			stat;

	if (signal_set_state_default() || set_fd_stream(info) < 0)
		exit(EXIT_FAILURE);
	unit = info->units->arr + info->cur_idx; // 변하지 않는 값이므로 const 변수로 선언하는게 좋았을 것 같다.
	argv = unit->argv;	// 이것도 마찬가지.
	if (is_builtin_command(argv[0]) != FALSE)
	// 'FALSE가 아니라면'이라고 부정형을 부정하기 보다는 'TRUE라면'(only 긍정)이 더 읽기 좋았을 것 같다.
	{
		stat = exec_builtin_cmd(unit, SUBSHELL);
		if (stat != CODE_OK)
			exit(EXIT_FAILURE);
		exit(CODE_OK);
	}
	child_exec_extern(info);
}
