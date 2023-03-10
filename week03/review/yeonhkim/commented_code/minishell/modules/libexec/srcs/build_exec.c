/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:02:36 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "exec_internal.h"

static int	init_unit(t_exec_unit *unit, t_node *simple_cmd)
{
	const int	n_redir = get_n_redir(simple_cmd);
	const int	n_word = node_getntokens(simple_cmd) - 2 * n_redir;

	unit->argv = (char **)malloc(sizeof(char *) * (n_word + 1));
	unit->redir_arr = (t_redir *)malloc(sizeof(t_redir) * (n_redir + 1));
	unit->n_word = n_word;
	unit->n_redir = n_redir;
	ft_bzero(unit->argv, sizeof(char *) * (n_word + 1));
	ft_bzero(unit->redir_arr, sizeof(t_redir) * (n_redir + 1));
	if (!unit->argv || !unit->redir_arr)
		return (free_unit_member(unit));
	return (CODE_OK);
}

static int	set_argv(t_node *node, t_exec_unit *unit, int idx)
{
	unit->argv[idx] = ft_strdup(node->content);
	if (!unit->argv[idx])
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

// unit이 아니라 redir_arr를 넘겨받는게 더 좋았을 것 같다.
static int	set_redir_arr(t_node *node, t_exec_unit *unit, int idx)
{
	t_node	*terminal_node;
	t_list	*curr;

	node = get_child_node(node, 1);
	curr = node->childs;
	terminal_node = curr->content;
	if (ft_strncmp(terminal_node->content, "<<", 2) == 0)
		unit->redir_arr[idx].type = REDIR_IN_HERE;
	else if (ft_strncmp(terminal_node->content, ">>", 2) == 0)
		unit->redir_arr[idx].type = REDIR_OUT_APPEND;
	else if (ft_strncmp(terminal_node->content, "<", 1) == 0)
		unit->redir_arr[idx].type = REDIR_IN;
	else if (ft_strncmp(terminal_node->content, ">", 1) == 0)
		unit->redir_arr[idx].type = REDIR_OUT;
	else
		unit->redir_arr[idx].type = REDIR_NONE;
	terminal_node = curr->next->content;
	unit->redir_arr[idx].content = ft_strdup(terminal_node->content);
	if (!unit->redir_arr[idx].content)
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

static int	build_unit(t_exec_unit *unit, t_node *simple_cmd)
{
	int			i;
	int			j;
	t_node		*node;
	t_list		*curr;

	if (init_unit(unit, simple_cmd) == CODE_ERROR_MALLOC)
		return (CODE_ERROR_MALLOC);
	i = 0;
	j = 0;
	curr = simple_cmd->childs;
	while (curr)
	{
		node = get_child_node(curr->content, 1);
		if (node->type == NODETYPE_CMD_WORD)
		{
			if (set_argv(node, unit, i++) == CODE_ERROR_MALLOC)
				return (free_single_unit(unit, i, j));
		}
		else
			if (set_redir_arr(node, unit, j++) == CODE_ERROR_MALLOC)
				return (free_single_unit(unit, i, j));
		curr = curr->next;
	}
	return (CODE_OK);
}

int	build_exec_unit(t_node *root, t_unit_arr *units)
{
	const int	n_unit = get_n_unit(root);
	t_list		*curr;
	int			idx;

	units->arr = (t_exec_unit *)malloc(sizeof(t_exec_unit) * n_unit);
	if (!units->arr)
		return (CODE_ERROR_MALLOC);
	units->n_unit = n_unit;
	ft_bzero(units->arr, n_unit * sizeof(t_exec_unit));
	curr = root->childs;
	idx = -1;
	while (++idx < n_unit)
	{
		if (build_unit(units->arr + idx, curr->content) == CODE_ERROR_MALLOC)
			return (free_all_unit(units, idx));
		curr = curr->next;
	}
	return (CODE_OK);
}
