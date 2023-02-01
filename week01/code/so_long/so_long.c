/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:28:38 by jibang            #+#    #+#             */
/*   Updated: 2022/07/05 17:04:24 by jibang           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_params	var;
	int			x;
	int			y;

	if (ac != 2)
		ft_perror_exit("Invalid arg number");
	var = ft_map_parsing(&var, av);
	if (find_forbidden_deco(var.map_line) == TRUE)
		ft_perror_exit("Forbidden decorations");
	var.mlx_ptr = mlx_init();
	x = var.map_width * DOTS;
	y = (var.map_height - 1) * DOTS;
	var.win_ptr = mlx_new_window(var.mlx_ptr, x, y, "jibang");
	var.step = 0;
	var.collect_now = 0;
	ft_put_images(var);
	mlx_hook(var.win_ptr, KEY_RELEASE, 0, &key_press, &var);
	mlx_hook(var.win_ptr, RED_X, 0, &game_exit, &var);
	mlx_loop(var.mlx_ptr);
	return (0);
}
