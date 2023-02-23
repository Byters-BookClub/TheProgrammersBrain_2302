/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:55 by jonkim            #+#    #+#             */
/*   Updated: 2023/02/24 05:29:56 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_ast	*make_ast_node(t_token_list *list)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	if (!list)
		node->type = PIPELINE;
		// NULL이면 node type
	else
	{
		node->data = ft_strdup(list->token.str);
		node->type = list->token.type;
	}
	return (node);
}

t_ast	*add_ast_node(t_ast *parent, t_ast *child)
{
	t_ast	*root;

	if (!parent || !child)
		return (NULL);
	if (parent->type == PIPELINE)
		root = add_pl_node(parent, child);
	else if (parent->type == PIPE)
		root = add_pipe_node(parent, child);
	else if (parent->type == REDIRECT)
		root = add_redirect_node(parent, child);
	else if (parent->type == WORD)
		root = add_cmd_node(parent, child);
	else
		root = NULL;
	return (root);
}

t_ast	*make_ast(t_token_list *list)
{
	t_token_list	*cur;
		// cur_tok이 더 좋을듯
	t_ast			*root;
	t_ast			*node;

	root = make_ast_node(NULL);
		// 엥 NULL을 왜 넣지
	cur = list ->next;
	while (cur)
	{
		node = make_ast_node(cur);
		if (!node)
			return (NULL);
		root = add_ast_node(root, node);
		cur = cur -> next;
	}
	return (root);
}
