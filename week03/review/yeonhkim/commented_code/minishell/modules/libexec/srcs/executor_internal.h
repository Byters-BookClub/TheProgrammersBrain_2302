/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:51:16 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// exec_internal.h와 executor_internal.h와 이름이 거의 비슷해서 조금 헷갈린다.

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include "t_exec_unit.h"

// 관련이 있는 매크로 상수들은 enum으로 묶어져 있었으면 좋았을 것 같다.

# define WRITE 1
# define READ 0

// io_manager에서 사용하는 두 가지의 모드
# define STDINOUT_BACKUP 0
# define STDINOUT_RESTORE 1

# define SUBSHELL 0			// 보너스까지 하지 않았다고 들었는데 서브쉘이 있네?
# define PARENTSHELL 1

typedef struct s_info
{
	t_unit_arr	*units;	// 배열의 주소 자체는 포인터로 이미 t_unit_arr에 들어있으므로, 이 멤버는 포인터일 필요가 없다.
						// 그냥 t_unit_arr 타입으로 두는 것이 의미상 더 맞았을 것 같다.
	int			n_unit;	// 음??? 이거 t_unit_arr에 들어있는 값인데? 이럴거면 왜 t_unit_arr를 두고 있는거지?
	int			cur_idx;
	int			new_pipe[2];
	int			old_pipe[2];
}	t_info;
// execute unit 배열과 pipe fd값들이 들어있는 것을 보아 하나의 pipeline을 실행하는데 필요한 정보들을 모아두는 구조체 같다.
// 보너스까지 하지 않았으므로 무조건 한번에 하나의 pipeline만을 실행하게 되었을 것이라, t_info도 적절한 이름 같다.
// (나 같은 경우 여러 개의 pipeline을 처리했어야 했으므로 구조체 명도 t_pipeline이 되었다.)

typedef int	(*t_do_redir)(t_redir *redir_arr);
typedef int	(*t_exec_builtin)(char **argv);

// 리다이렉트 처리
int		process_redir(t_redir *redir_arr, int n_redir);
	// 이름이 통일성 있어서 보기 좋다.
int		do_redir_in(t_redir *redir_arr);
int		do_redir_out(t_redir *redir_arr);
int		do_redir_in_here(t_redir *redir_arr);
int		do_redir_out_append(t_redir *redir_arr);

int		io_manager(int mode);

// 자식 프로세스에서 실행
void	child_exec_cmd(t_info *info);

// 부모 프로세스에서 실행
int		exec_builtin_cmd(t_exec_unit *unit, int mode);

#endif
