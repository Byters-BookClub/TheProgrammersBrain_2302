/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:37:22 by hyunjcho          #+#    #+#             */
/*   Updated: 2023/02/24 03:37:52 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	fork_process(void)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	// 자식 하나 만들고 바로 wait이 나오네. 병렬 처리는 안하셨나?
	// 근데 상당히 깔끔하다...
	// 함수 이름이 fork_process라서 파일 디스크립터 값을 반환하는 것이 처음에는 요상하게 느껴졌으나
	// 상당히 구성이 깔끔하다...
	wait(&status);
	close(fd[1]);
	return (fd[0]);
}
