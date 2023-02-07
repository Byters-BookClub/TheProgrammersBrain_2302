/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:01:31 by jibang            #+#    #+#             */
/*   Updated: 2022/07/03 13:18:17 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_params *var)
{
	t_pos	pos;

	pos = find_player_pos(*var);
	if (var->map_line[pos.i - var->map_width] == WALL)
		return ;
	else if (var->map_line[pos.i - var->map_width] == SPACE)
	{
		pos.tmp = var->map_line[pos.i];
		var->map_line[pos.i] = var->map_line[pos.i - var->map_width];
		var->map_line[pos.i - var->map_width] = pos.tmp;
		(var->step)++;
	}
	else if (var->map_line[pos.i - var->map_width] == 'C')
	{
		var->map_line[pos.i - var->map_width] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
		(var->collect_now)++;
	}
	else if (check_finish_game(var) == SUCCESS)
	{
		var->map_line[pos.i - var->map_width] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
	}
}

void	move_down(t_params *var)
{
	t_pos	pos;

	pos = find_player_pos(*var);
	if (var->map_line[pos.i + var->map_width] == WALL)
		return ;
	else if (var->map_line[pos.i + var->map_width] == SPACE)
	{
		pos.tmp = var->map_line[pos.i];
		var->map_line[pos.i] = var->map_line[pos.i + var->map_width];
		var->map_line[pos.i + var->map_width] = pos.tmp;
		(var->step)++;
	}
	else if (var->map_line[pos.i + var->map_width] == 'C')
	{
		var->map_line[pos.i + var->map_width] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
		(var->collect_now)++;
	}
	else if (check_finish_game(var) == SUCCESS)
	{
		var->map_line[pos.i + var->map_width] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
	}
}

void	move_right(t_params *var)
{
	t_pos	pos;

	pos = find_player_pos(*var);
	if (var->map_line[pos.i + 1] == WALL)
		return ;
	else if (var->map_line[pos.i + 1] == SPACE)
	{
		pos.tmp = var->map_line[pos.i];
		var->map_line[pos.i] = var->map_line[pos.i + 1];
		var->map_line[pos.i + 1] = pos.tmp;
		(var->step)++;
	}
	else if (var->map_line[pos.i + 1] == 'C')
	{
		var->map_line[pos.i + 1] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
		(var->collect_now)++;
	}
	else if (check_finish_game(var) == SUCCESS)
	{
		var->map_line[pos.i + 1] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
	}
}

void	move_left(t_params *var)
{
	t_pos	pos;

	pos = find_player_pos(*var);
	if (var->map_line[pos.i - 1] == WALL)
		return ;
	else if (var->map_line[pos.i - 1] == SPACE)
	{
		pos.tmp = var->map_line[pos.i];
		var->map_line[pos.i] = var->map_line[pos.i - 1];
		var->map_line[pos.i - 1] = pos.tmp;
		(var->step)++;
	}
	else if (var->map_line[pos.i - 1] == 'C')
	{
		var->map_line[pos.i - 1] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
		(var->collect_now)++;
	}
	else if (check_finish_game(var) == SUCCESS)
	{
		var->map_line[pos.i - 1] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
	}
}

int	key_press(int keycode, t_params *var)
{
	if (keycode == W_KEY)
		move_up(var);
	else if (keycode == S_KEY)
		move_down(var);
	else if (keycode == D_KEY)
		move_right(var);
	else if (keycode == A_KEY)
		move_left(var);
	else if (keycode == ESC_KEY)
		exit(0);
	printf("step : %d\n", var->step);
	ft_put_images(*var);
	return (0);
}
