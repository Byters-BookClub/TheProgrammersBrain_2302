/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:33:19 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/24 00:43:17 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"

int	executor(t_node *parse_tree)
{
	if (execute_list(parse_tree) == SUCCESS) //트리구조 실행인데 왜 list라는 이름이 붙었을까?
		return (SUCCESS);
	else
		return (FAILURE);
}
