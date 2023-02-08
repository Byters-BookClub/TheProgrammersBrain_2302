/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:01:21 by jibang            #+#    #+#             */
/*   Updated: 2023/02/08 13:06:39 by yeonhkim         ###   ########.fr       */
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

// collection의 개수를 세어 반환하는 함수이므로 만약 동사를 함수명 맨 앞에 넣고싶다면 count_num_of_collection 혹은 count_collection 등이 좋을 것 같음
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

// deco가 무엇일까?
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
			sign = TRUE;	// 처음에는 false인 값이 여기서 true로 바뀌는 것을 보니까 아마 C, E, P, Wall, Space가 아닌 나머지 것을 deco라고 칭하는 모양이다.
		}
		i++;
	}
	return (sign);
}
// 어차피 true 혹은 false이며, 5개 중 하나에 해당되지 않는 값이 하나라도 존재하는 경우 true를 return하므로,
// 굳이 sign 변수를 두기보다는 sign = TRUE; -> return (TRUE);
// 모든 검사를 마친 후 마지막 리턴인 return (sign); -> return (FALSE); 인 편이 좋을 것 같다. 
