/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execute_unit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:30:31 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/24 10:34:53 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tree_internal.h"

t_execute_unit	*create_execute_unit(int node_type)
{
	t_execute_unit	*new;

	new = ft_malloc(sizeof(t_execute_unit));
	new->cmd_argv = NULL;
	new->redir_list = NULL;
	if (node_type == NODE_SUBSHELL)
	{
		new->cmd_name = NULL;
		new->q_cmd_argv = NULL;
		new->q_redir_list = create_queue(QUEUE_INITIAL_SIZE, QUEUE_INTSTR); //실행은 큐구조로 담아서 하는구나..신기하다
	}
	else if (node_type == NODE_SIMPLE_CMD)
	{
		new->cmd_name = NULL;
		new->q_cmd_argv = create_queue(QUEUE_INITIAL_SIZE, QUEUE_STR_ONLY);
		new->q_redir_list = create_queue(QUEUE_INITIAL_SIZE, QUEUE_INTSTR);
	}
	return (new);
}
