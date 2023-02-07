/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:17:35 by jibang            #+#    #+#             */
/*   Updated: 2022/07/02 21:00:09 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_info(t_params var)
{
	t_string	str;
	int			x;
	int			y;
	int			x1;

	str.col = ft_itoa(var.collect_now);
	str.mis = ft_itoa(var.collect_goal);
	str.step = ft_itoa(var.step);
	x = DOTS / 6;
	y = DOTS / 4;
	x1 = 5 * DOTS / 7;
	mlx_string_put(var.mlx_ptr, var.win_ptr, x, y, 0x00000000, "STEP");
	mlx_string_put(var.mlx_ptr, var.win_ptr, x1, y, 0x00000000, str.step);
	mlx_string_put(var.mlx_ptr, var.win_ptr, x, 2 * y, 0x00000000, "GOAL");
	mlx_string_put(var.mlx_ptr, var.win_ptr, x1, 2 * y, 0x00000000, str.mis);
	mlx_string_put(var.mlx_ptr, var.win_ptr, x, 3 * y, 0x00000000, "NOW");
	mlx_string_put(var.mlx_ptr, var.win_ptr, x1, 3 * y, 0x00000000, str.col);
}

void	put_background(t_params var, t_image image)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	j = 0;
	while (var.map_line[i])
	{
		x = (i % var.map_width) * DOTS;
		y = j * DOTS;
		mlx_put_image_to_window(var.mlx_ptr, var.win_ptr, image.grass, x, y);
		i++;
		if (i % var.map_width == 0)
			j++;
	}
}

void	put_decorations(t_params var, t_image image)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	j = 0;
	while (var.map_line[i])
	{
		x = (i % var.map_width) * DOTS;
		y = j * DOTS;
		if (var.map_line[i] == WALL)
			mlx_put_image_to_window(var.mlx_ptr, var.win_ptr, image.box, x, y);
		else if (var.map_line[i] == 'C')
			mlx_put_image_to_window(var.mlx_ptr, var.win_ptr, image.bird, x, y);
		else if (var.map_line [i] == 'E')
			mlx_put_image_to_window(var.mlx_ptr, var.win_ptr, image.tile, x, y);
		i++;
		if (i % var.map_width == 0)
			j++;
	}
}

void	put_hero(t_params var, t_image image)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	j = 0;
	while (var.map_line[i])
	{
		x = (i % var.map_width) * DOTS;
		y = j * DOTS;
		if (var.map_line[i] == 'P')
			mlx_put_image_to_window(var.mlx_ptr, var.win_ptr, image.hero, x, y);
		i++;
		if (i % var.map_width == 0)
			j++;
	}
}

void	ft_put_images(t_params var)
{
	t_image		img;
	int			w;
	int			h;

	if (check_e_finished(var) == TRUE)
	{
		printf("Mission Complete!");
		exit(0);
	}
	img.hero = mlx_xpm_file_to_image(var.mlx_ptr, "./src/hero.xpm", &w, &h);
	img.bird = mlx_xpm_file_to_image(var.mlx_ptr, "./src/bird.xpm", &w, &h);
	img.grass = mlx_xpm_file_to_image(var.mlx_ptr, "./src/grass.xpm", &w, &h);
	img.box = mlx_xpm_file_to_image(var.mlx_ptr, "./src/box.xpm", &w, &h);
	img.tile = mlx_xpm_file_to_image(var.mlx_ptr, "./src/tile.xpm", &w, &h);
	put_background(var, img);
	put_decorations(var, img);
	put_hero(var, img);
	put_info(var);
}
