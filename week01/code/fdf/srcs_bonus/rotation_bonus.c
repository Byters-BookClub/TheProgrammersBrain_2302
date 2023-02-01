/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 02:47:06 by dahkang           #+#    #+#             */
/*   Updated: 2022/12/28 17:29:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	rotate_x(t_vertex *v, double alpha)
{
	const int	prev_x = v->x;
	const int	prev_y = v->y;
	const int	prev_z = v->z;

	v->x = prev_x;
	v->y = cos(alpha) * prev_y - sin(alpha) * prev_z;
	v->z = sin(alpha) * prev_y + cos(alpha) * prev_z;
}

void	rotate_y(t_vertex *v, double beta)
{
	const int	prev_x = v->x;
	const int	prev_y = v->y;
	const int	prev_z = v->z;

	v->x = cos(beta) * prev_x - sin(beta) * prev_z;
	v->y = prev_y;
	v->z = sin(beta) * prev_x + cos(beta) * prev_z;
}

void	rotate_z(t_vertex *v, double gamma)
{
	const int	prev_x = v->x;
	const int	prev_y = v->y;
	const int	prev_z = v->z;

	v->x = cos(gamma) * prev_x - sin(gamma) * prev_y;
	v->y = sin(gamma) * prev_x + cos(gamma) * prev_y;
	v->z = prev_z;
}
