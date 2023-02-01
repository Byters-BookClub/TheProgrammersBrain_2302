/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:33:03 by dahkang           #+#    #+#             */
/*   Updated: 2022/12/28 17:27:09 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/fdf_bonus.h"
#include "../includes/key_codes_bonus.h"

static void	translation(int key, t_vars *vars)
{
	if (key == UP)
		vars->y_translate -= 10;
	else if (key == DOWN)
		vars->y_translate += 10;
	else if (key == LEFT)
		vars->x_translate -= 10;
	else if (key == RIGHT)
		vars->x_translate += 10;
}

static void	zoom(int key, t_vars *vars)
{
	if (key == PLUS && vars->x_scale <= 500 \
		&& vars->y_scale <= 500 && vars->z_scale <= 500)
	{
		vars->x_scale += 0.05;
		vars->y_scale += 0.05;
		vars->z_scale += 0.05;
		vars->x_scale *= 1.3;
		vars->y_scale *= 1.3;
		vars->z_scale *= 1.3;
	}
	else if (key == MINUS && vars->x_scale >= 0.002 \
			&& vars->y_scale >= 0.002 && vars->z_scale >= 0.002)
	{
		vars->x_scale *= 0.7;
		vars->y_scale *= 0.7;
		vars->z_scale *= 0.7;
	}
}

static void	rotate(int key, t_vars *vars)
{
	if (key == Q)
		vars->alpha += M_PI / 6;
	else if (key == W)
		vars->alpha -= M_PI / 6;
	else if (key == A)
		vars->beta += M_PI / 6;
	else if (key == S)
		vars->beta -= M_PI / 6;
	else if (key == Z)
		vars->gamma += M_PI / 6;
	else if (key == X)
		vars->gamma -= M_PI / 6;
}

static void	scaling(int key, t_vars *vars)
{
	if (key == R && vars->x_scale <= 500)
	{
		vars->x_scale += 0.05;
		vars->x_scale *= 1.3;
	}
	else if (key == T && vars->x_scale >= 0.002)
		vars->x_scale *= 0.7;
	else if (key == F && vars->y_scale <= 500)
	{
		vars->y_scale += 0.05;
		vars->y_scale *= 1.3;
	}
	else if (key == G && vars->y_scale >= 0.002)
		vars->y_scale *= 0.7;
	else if (key == V && vars->z_scale <= 500)
	{
		vars->z_scale += 0.05;
		vars->z_scale *= 1.3;
	}
	else if (key == B && vars->z_scale >= 0.002)
		vars->z_scale *= 0.7;
}

int	key_hook(int key, t_mlx *mlx_info)
{
	if (key == ESC)
		exit(0);
	if (key == I)
		iso_proj(mlx_info->vars);
	else if (key == P)
		parellel_proj(mlx_info->vars);
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		translation(key, mlx_info->vars);
	else if (key == PLUS || key == MINUS)
		zoom(key, mlx_info->vars);
	else if (key == Q || key == W || key == A \
				|| key == S || key == Z || key == X)
		rotate(key, mlx_info->vars);
	else if (key == R || key == T || key == F \
				|| key == G || key == V || key == B)
		scaling(key, mlx_info->vars);
	return (1);
}
