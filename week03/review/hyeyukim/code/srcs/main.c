/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:59:15 by hyunjcho          #+#    #+#             */
/*   Updated: 2023/02/24 03:40:56 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_line(t_pl_list *list, char **envp, int count)
{
	int	next_in_fd; // 다음 파이프라인한테 넘겨줄 입력 파일디스크립터로 추측됨
	int	flag; // 무엇에 대한 플래그일까...

	next_in_fd = STDIN_FILENO;
	flag = FALSE;
	while (list)
	{
		list->pipeline->in_fd = next_in_fd;
		if (!list->next)
			list->pipeline->out_fd = 1;
// ast가 뭐지...? abstract?
// 아 맞다... minishell parsing tree 구현할 때 abstract syntax tree가 나오지..
// 저번에 연결리스트로 구현했다고 하신 것 같은데 아니었나...?
		ast_redirect_process(list->pipeline);
		if (list->pipeline->in_fd == -1 || list->pipeline->out_fd == -1)
		{
			update_exit_code(ft_strdup("1"));
			list = list->next;
			// fork_process 반환값이 파일 디스크립터 값...?
			next_in_fd = fork_process();
			continue ;
		}
		// execute_cmd 반환값이 파일 디스크립터 값...?
		next_in_fd = execute_cmd(list->pipeline, envp, count);
		list = list->next;
	}
	if (next_in_fd != STDIN_FILENO)
		close(next_in_fd);
}

int	main(int ac, char **av, char **envp)
{
	char			*line;
	t_info			info;

	if (ac != 1)
		return (0);
// init이 initialize의 줄임말이라면 set과 init 중에 하나만 써도 되지 않았을까.
// 만약 initially의 줄임말이었다면 줄이지 않는게 나았을 수도
// 또한 초기화 대상이 무엇인지 대략적으로 함수 이름에 드러나면 좋을 것 같다.
// set_init -> init_setting
	set_init(envp, av);
	while (1)
	{
		line = readline("petitshell> ");
		if (!line)
		{
			printf("petitshell> exit\n");
			exit(EXIT_SUCCESS);
		}
// 초기화 함수가 두 개네...?
// main_init과 set_init의 차이는 무엇일까.
// set_init은 setting(signal, env list 등)을 처리하는 함수이고
// main_init은 info 구조체를 초기화하는 함수로 보인다.
// 각 명령줄을 파싱해서 이에 대한 정보를 저장하는 함수로 보이는데
// 아래에 execute_line도 있으니까 이건 parse_line도 괜찮을 것 같다.
// man_init -> parse_line
		else if (!*line || main_init(line, &info) == FAIL)
		{
			free(line);
			continue ;
		}
		execute_line(info.pl->next, envp, info.pipe_count);
// 동사 뒤에 대상이 오는 것이 문법적으로 더 자연스러울 것 같다.
// all_free -> free_all
		all_free(&info);
// 위에 다 free한다고 했는데 line만 따로 free 하는 것이 조금 어색한 것 같다.
// 위 함수를 all_free-> free_line_info 같은 방식으로 대상을 지정해주면 좋을 것 같다.
// 아니면 line도 all_free 함수 내부에서 free 하는 것도 괜찮을 것 같다.
		free(line);
	}
	return (0);
}
