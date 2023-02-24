/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:51:05 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "strutils.h"
#include "executor_internal.h"

// 보통 자식 프로세스(child process)의 복수형으로 'child processes' 혹은 'childs' 정도를 쓸 텐데,
// children이라니 생각치도 못 했다. 재밌다.
static int	wait_children(pid_t last_cmd, int n_unit)
// 함수명에 맞춰서 파라미터 명을 명명했으면 이 함수만 따로 떼고 보더라도 무슨 일을 하는 함수인지 잘 알 수 있었을 것 같다.
	// last_cmd는 'last_child' 혹은 'last_child_pid'
	// n_unit은 'n_child' 정도로...
{
	int	i;			// 이 함수에 있어 주요한 변수가 아니니 세 변수들 중 가장 아래에 선언하는 것이 좋았을 것 같다.
	int	status;			
	int	exit_status;	// 바로 위쪽의 status 변수도 사실 종료 상태(exit status)를 저장하고 있는 변수이므로,
						// 마지막 자식 프로세스의 exit status라는 점이 드러나는 이름이었으면 더 좋았을 것 같다.

	exit_status = 1;
	i = -1;	// i의 값은 0부터 시작하는게 좋을 것 같다.
	while (++i < n_unit)	// while 반복문의 조건문에서 증감 연산자를 사용하지 않는 것이 더 좋을 것 같다.
	{
		if (last_cmd == wait(&status))
		// wait의 반환값 일치 여부를 확인하는 것이므로, 앞뒤 순서를 뒤집어서 'wait(&status) == last_cmd'가 더 읽기 좋았을 것 같다.
		{
			if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + 128;
			else
				exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}

// 사용하지 않는 pipe를 닫는 행위는 부모에서 하는 것이 (적어도 이 소스 내에서는)확실하므로,
// parent_ 접두어는 없어도 되었을 것 같기도? (게다가 이 함수는 static 함수이다)
static int	parent_close_unused_pipe(t_info *info)
{
	int	stat;

	stat = CODE_OK;
	if (info->units->n_unit == 1)	// 처리할 필요가 없어 함수를 바로 탈출하는 부분이므로 맨 위에 있는 것이 좋을 것 같다.
		return (CODE_OK);
	if (info->cur_idx == 0)
		stat = close(info->new_pipe[WRITE]);
	else if (info->cur_idx == info->n_unit - 1)
		stat = close(info->old_pipe[READ]);
	else
		if (close(info->old_pipe[READ]) < 0 || close(info->new_pipe[WRITE]) < 0)
		// else 논리 연산자에서 타고 들어오는 부분인데, 바로 if 문으로 반환값을 확인하여 에러 처리를 하다보니 조금 헷갈려보이기도 한다.
		// 하지만 분명 필요한 에러 처리이고, 이걸 한 줄로 다 처리하니 코드가 간결해져서 좋긴하다.
		// 중괄호를 생략하지 않고 close 함수 호출마다 줄을 나눠두었으면 읽기 더 좋았을 듯.
			return (CODE_ERROR_IO);
	return (stat);
}

static void	init_info(t_info *info, t_unit_arr *units)
{
	info->units = units;
	info->n_unit = units->n_unit;
	info->cur_idx = 0;	// unit arr에서 이 idx를 사용하나보다....
}

static int	fork_exec(t_unit_arr *units)
// 자식 프로세스를 하나 이상 fork해서 실행한다는 의미로 fork_exec으로 한 것 같다.
// 자식 프로세스를 fork하는 것에 더불어 실행까지 내부에서 하고 있으므로, '실행한다'는 의미가 함수명에 들어갔으면 더 좋았을 것 같다.
{
	t_info	info;
	pid_t	pid;

	init_info(&info, units);
	while (info.cur_idx < info.n_unit) // 어차피 0부터 시작할건데 왜 cur_idx 멤버가 굳이 있는거지?? 반복문용 변수 i를 사용하는 것이 더 적절했을 것 같다.
	{
		if (info.cur_idx < info.n_unit - 1)
		// '마지막이 아닌 경우'에 실행하는 것이므로 'info.cur_idx != info.n_unit - 1'가 좀더 읽기 좋았을 것 같다.
			if (pipe(info.new_pipe) < 0)
			// 중괄호도 없이 조건문이 연속해서 있으니 읽기가 힘든 측면이 있다. 다른 곳에서 했던 것처럼 논리연산자를 통해 하나의 조건문으로 엮는 편이 더 보기 좋았을 것 같다.
				return (CODE_ERROR_IO);
		pid = fork();
		if (pid < 0)
			return (CODE_ERROR_GENERIC);
		if (pid == 0)
			child_exec_cmd(&info);
		if (parent_close_unused_pipe(&info) < 0)
			return (CODE_ERROR_IO);
		ft_memcpy(info.old_pipe, info.new_pipe, sizeof(info.new_pipe));
		info.cur_idx++;
	}
	return (wait_children(pid, info.n_unit));
}

int	executor(t_unit_arr *units)	// 하나의 파이프라인을 이루는 실행 단위들을 각각의 unit으로 칭하는 듯
{
	int	stat;	// exit_status를 저장하는 변수인 것 같다.
				// 읽다보니 exit_status가 아니었다......

	if (units->n_unit <= 0)			// unit의 개수가 0 이하일 수도 있나?
		return (CODE_ERROR_SCOPE);
	if (units->arr->n_word == 0)	// 이게 어떠한 경우지?
	{
		if (io_manager(STDINOUT_BACKUP))
			return (1);
		stat = process_redir(units->arr->redir_arr, units->arr->n_redir);
		if (io_manager(STDINOUT_RESTORE))
			return (1);
		if (stat == CODE_ERROR_IO)
			return (1);
		return (CODE_OK);
	}
	if (units->n_unit == 1
		&& is_builtin_command(units->arr->argv[0]))			// 단일 builtin인 경우 따로 처리하는 부분.
		return (exec_builtin_cmd(units->arr, PARENTSHELL));
	return (fork_exec(units));
}

// 에러 메세지의 출력 형태는 모두 거의 같으므로
// (stderr로 출력, MSG_ERROR_PREFIX를 전방에 붙임, 추가적인 string format은 들어갈 수도 있고 안 들어갈 수도 있음)
// 아예 에러 메세지 출력 전용 함수를 따로 두어도 좋았을 것 같다.
