/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:52:43 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/24 10:33:25 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

int	parse_list(t_node *node, t_token *tokens, int *offset)
{
	t_node	*new_node;

	if (parse_pipeline(node, tokens, offset) == FAILURE) //여기서부터 읽기가 힘들어졌다..
		return (FAILURE);
	if (!(tokens[*offset].type == TOKEN_AND_IF || \
										tokens[*offset].type == TOKEN_OR_IF))
		return (SUCCESS);
	new_node = create_tree_node(node->root);
	new_node->type = tokens[*offset].type;
	(*offset)++;
	new_node->first_child = *(node->root); // root는 어떤 역할을 하는가
	*(node->root) = new_node;
	new_node->first_child->next_sibling = create_tree_node(node->root);
	 // 재귀구조,
	if (parse_list(new_node->first_child->next_sibling, tokens, offset) \
																	== FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
