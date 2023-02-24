/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:54:11 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/24 10:34:03 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static int	parse_command(t_node *node, t_token *tokens, int *offset) // 이름이 좀 계속 헷갈린다.. 트리 만드는건데 토크나이징=파싱 이게 머리에 박혀서 그런듯
{
	int	res;

	if (tokens[*offset].type == TOKEN_LPAREN)
		res = parse_subshell(node, tokens, offset);
	else
		res = parse_simple_command(node, tokens, offset);
	return (res);
}

int	parse_pipeline(t_node *node, t_token *tokens, int *offset)
{
	t_node	*cur_node;

	node->type = NODE_PIPELINE;
	node->first_child = create_tree_node(node->root);
	if (parse_command(node->first_child, tokens, offset) == FAILURE) // 파이프 양옆에 커맨드 노드를 트리구조로 만들어 주는 과정인듯
		return (FAILURE);
	cur_node = node->first_child;
	while (tokens[*offset].type == TOKEN_PIPE)
	{
		(*offset)++;
		cur_node->next_sibling = create_tree_node(node->root);
		if (parse_command(cur_node->next_sibling, tokens, offset) \
															== FAILURE)
			return (FAILURE);
		cur_node = cur_node->next_sibling;
	}
	return (SUCCESS);
}
