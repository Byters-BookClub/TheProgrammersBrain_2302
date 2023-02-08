/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:28:38 by jibang            #+#    #+#             */
/*   Updated: 2023/02/07 16:54:32 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_perror_exit(char *s)
{
	perror(s);
	exit(1);
}

int	game_exit(int keycode, t_params *var)
{
	(void)(*var);
	(void)keycode;
	exit(0);
}

int	main(int ac, char **av)	// 통상적으로 사용하는 파라미터 명이 아니라서 순간 흠칫했지만 이해하는 데는 무리가 없다.
{
	t_params	var;
	int			x;
	int			y;

	if (ac != 2)
		ft_perror_exit("Invalid arg number");
	var = ft_map_parsing(&var, av);					// ft_를 접두어로 붙인 이유가 있을까?
	if (find_forbidden_deco(var.map_line) == TRUE)	// forbidden deco? 뭔지 모르겠지만 궁금하다.
		ft_perror_exit("Forbidden decorations");
	var.mlx_ptr = mlx_init();

	// 이 코드들은 하나로 묶어서 init_var라는 이름의 함수로 두면 좋을 것 같다.
	x = var.map_width * DOTS;
	y = (var.map_height - 1) * DOTS;
	var.win_ptr = mlx_new_window(var.mlx_ptr, x, y, "jibang");
	var.step = 0;
	var.collect_now = 0;

	ft_put_images(var);
	mlx_hook(var.win_ptr, KEY_RELEASE, 0, &key_press, &var);
	mlx_hook(var.win_ptr, RED_X, 0, &game_exit, &var); // 레드_x가 뭐지?
	mlx_loop(var.mlx_ptr);
	return (0);
}
