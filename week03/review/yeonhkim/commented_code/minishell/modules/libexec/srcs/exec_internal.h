/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 12:07:14 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// exec_internal.h와 executor_internal.h와 이름이 거의 비슷해서 조금 헷갈린다.

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "t_node.h"
# include "t_exec_unit.h"

int		get_n_unit(t_node *root);
int		get_n_redir(t_node *node);
t_node	*get_child_node(t_node *cmd_elem, int depth);

int		free_unit_member(t_exec_unit *unit);
int		free_single_unit(t_exec_unit *unit, int i, int j);
int		free_all_unit(t_unit_arr *units, int idx);

#endif
