/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:32:35 by jonkim            #+#    #+#             */
/*   Updated: 2023/02/24 05:30:31 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	pipe_counting(t_info *info)
{
	t_token_list	*cur;

	cur = info->list;
	while (cur)
	{
		if (cur->token.type == PIPE)
		{
			info->pipe_count = TRUE;
			break ;
		}
		cur = cur->next;
	}
		// 역시 추측했던 대로 토큰 타입이 파이프인 개수를 세는 함수구마잉
}

int	main_init(char *line, t_info *info)
{
	add_history(line);
		// 히스토리에 추가했구나
	ft_memset(info, 0, sizeof(t_info));
		// 일단 0으로 구조체 내용 다 초기화했구나
	info->list = make_token_list(tokenize(line));
		// 명령줄의 내용을 토크나이징해서 토큰 리스트를 생성했구나
	env_sub(info->list);
		// env는 environment 말하는 것 같고 sub는 뭐지 설마 substitute?
		// 줄이지 않는게 좋았을수도
	info->ast = make_ast(info->list);
		// abstract syntax tree를 말하는 거 맞겠지?
		// tree 안썼다고 하셨던 것 같은데 내 기억이 잘못됬나봄
	if (syntax_check(info->ast) == FAIL)
	{
		update_exit_code(ft_strdup("258"));
		return (FAIL);
	}
		// 트리 순회하면서 syntax 체크를 하네
		// 원래 abstract syntax tree는 생성하면서 syntax 체크해주는 거 아닌가
	pipe_counting(info);
		// 파이프 파일 개수를 세나보군
	ast_merge(info->ast);
		// abstract syntax tree로 추정되는데 무엇을 merge한다는 걸까?
		// merge 대상이 좀 더 구체적으로 명시되어있다면...?
	info->pl = pl_list(info->ast);
		// pl은 pipe line의 줄임말로 추정됨
		// pipeline의 연결리스트를 생성하는군
		// 아 실행부가 쉽게 실행할 수 있도록 연결리스트로 바꾸는건가보군
	return (SUCCESS);
}

int	set_init(char **envp, char **av)
{
	(void)av; 
		// ? 매개변수로 왜 받아온거지?
		// 아... main문에다가 (void)av 쓰는게 싫었구나...
		// 혹시 norm 때문이었나...
		// 만약 norm 25줄 때문이었다면 main 함수 내용을 두 함수 내용으로 나누는게 나았을듯
	init_env(envp);
		// environment variable 초기화했구나
	signal_init();
		// signal setting 했구나
	setechoctl(1);
		// 터미널 속성 setting 했구나
	print_art();
		// 처음에 쉘 welcome 문구 출력했구나
	return (SUCCESS);
}
