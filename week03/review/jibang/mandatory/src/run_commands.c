/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:37:36 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/24 13:27:02 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "handle_error.h"

static void	execute(t_node *parse_tree, int *errcode)
{
	if (*errcode == FAILURE)
		return ;
	*errcode = executor(parse_tree);
}

static void	make_parse_tree(t_token *tokens, t_node **parse_tree, int *errcode)
{
	if (*errcode == FAILURE)
		return ;
	*errcode = parser(tokens, parse_tree); // 띠용.. lexer가 파서인줄 알았는데 파서가 또 있었구나
}

static void	tokenizing(char *input, t_token **token_list, int *errcode)
{
	*errcode = lexer(input, token_list); // 렉서가 실제적인 토크나이징을 하는 구나. 에러가 생기면 리턴으로 errcode에 값을 전달하는 구나
	return ;
}

static void	free_allocated_memory(t_token *token_list, t_node *parse_tree)
{
	if (token_list)
		destroy_token_list(token_list);
	if (parse_tree)
		destroy_tree(parse_tree);
	return ;
}

void	run_commands(char *input) // 각 함수들이 하는 일을 잘 명시 해놨다.
{
	t_token	*token_list;
	t_node	*parse_tree;
	int		errcode;

	errcode = 0;
	token_list = NULL;
	parse_tree = NULL;
	tokenizing(input, &token_list, &errcode); // input 받은 것을 토큰 리스트에 달아 놓겠구나 예상. 에러 생기면 errcode로 받아오겠구나
	make_parse_tree(token_list, &parse_tree, &errcode);
	execute(parse_tree, &errcode);
	free_allocated_memory(token_list, parse_tree);
}
