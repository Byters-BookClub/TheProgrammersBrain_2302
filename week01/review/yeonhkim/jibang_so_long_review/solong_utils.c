/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:01:21 by jibang            #+#    #+#             */
/*   Updated: 2022/07/02 20:09:16 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_e_finished(t_params var)
{
	int		i;

	i = 0;
	while (var.map_line[i])
	{
		if (var.map_line[i] == 'E')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_pos	find_player_pos(t_params var)
{
	t_pos	pos;

	pos.i = 0;
	pos.j = 0;
	while (var.map_line[pos.i])
	{
		if (var.map_line[pos.i] == 'P')
		{
			pos.check = SUCCESS;
			return (pos);
		}
		(pos.i)++;
		if (pos.i % var.map_width == 0)
			(pos.j)++;
	}
	ft_perror_exit("No player");
	return (pos);
}

int	check_finish_game(t_params *var)
{
	if (var->collect_now == var->collect_goal)
	{
		return (SUCCESS);
	}
	return (ERROR);
}

int	number_of_collection(char *map_line)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (map_line[i])
	{
		if (map_line[i] == 'C')
			cnt++;
		i++;
	}
	return (cnt);
}

int	find_forbidden_deco(char *line)
{
	int		i;
	int		sign;

	sign = FALSE;
	i = 0;
	while (line[i])
	{
		if (line[i] != 'C' && line[i] != 'E' && line[i] != 'P'\
		&& line[i] != WALL && line[i] != SPACE)
		{
			sign = TRUE;
		}
		i++;
	}
	return (sign);
}
