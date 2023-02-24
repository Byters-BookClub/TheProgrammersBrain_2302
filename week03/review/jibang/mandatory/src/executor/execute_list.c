/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:03 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/24 10:56:16 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"

int	execute_list(t_node *node) // 실행은 left , right 트리 재귀구조로 도는 것 같은데 왜 리스트일까 이름이..실행큐는 언제 사용할까?
{
	if (node->type == NODE_PIPELINE)
		return (execute_pipeline(node->first_child)); // 재귀구조로 계속 돌면서 pipe노드까지
	else if (node->type == NODE_AND_IF)
	{
		if (execute_list(node->first_child) == EXIT_SUCCESS)
			execute_list(node->first_child->next_sibling);
	}
	else if (node->type == NODE_OR_IF)
	{
		if (execute_list(node->first_child) != EXIT_SUCCESS)
			execute_list(node->first_child->next_sibling);
	}
	return (SUCCESS);
}
