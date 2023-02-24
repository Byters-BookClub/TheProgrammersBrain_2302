/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:10:36 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_commands.h"
#include "executor_internal.h"

// is_builtin_command와 코드 내용이 겹친다.
// (전자는 참/거짓 판별을 위한 함수이긴 하지만 결국 함수의 행동은 같으며, 양쪽 모두가 사용하는 양수 반환값(인덱스)으로 양쪽이 원하는 기능을 수행할 수 있다)
static int	map_cmd(char *cmd)
{
	const char	*builtin_cmds[8] = {
		"",	// 왜 있는거지? 만약 이 문자열과 일치하면 0이 반환될텐데 그러면 어떻게 되는거지?
		"cd",
		"echo",
		"export",
		"pwd",
		"unset",
		"env",
		"exit"
	};
	const int	cmd_len = ft_strlen(cmd);
	int			i;

	i = -1;
	while (++i < 8)
		if (ft_strncmp(builtin_cmds[i], cmd, cmd_len + 1) == 0)
			return (i);
	return (CODE_ERROR_GENERIC);
}

int	exec_builtin_cmd(t_exec_unit *unit, int mode)
{
	const t_exec_builtin	exec_builtin[8] = {
		0, builtin_cd, builtin_echo, builtin_export,
		builtin_pwd, builtin_unset, builtin_env, builtin_exit
	};	// 0은 왜 있는거지? 없어도 되지 않나?
	const int				cmd_idx = map_cmd(unit->argv[0]);
	int						stat;

	if (mode == PARENTSHELL && io_manager(STDINOUT_BACKUP))
		return (1);
	stat = process_redir(unit->redir_arr, unit->n_redir);
	if (stat == CODE_ERROR_IO)
		return (1);
	if (cmd_idx == CODE_ERROR_GENERIC)
	// 이 함수로 들어오기 전 이미 is_builtin_command을 통해 builtin 명령어임을 확인하였기 때문에 필요 없는 예외처리이다.
	{
		ft_dprintf(2, "Failed to map proper cmd index\n");
		return (-1);
	}
	stat = exec_builtin[cmd_idx](unit->argv);
	if (mode == PARENTSHELL && io_manager(STDINOUT_RESTORE))
		return (1);
	return (stat);
}
