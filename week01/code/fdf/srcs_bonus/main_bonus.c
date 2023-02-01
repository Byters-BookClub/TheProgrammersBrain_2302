/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:02:23 by dahkang           #+#    #+#             */
/*   Updated: 2022/12/28 18:34:57 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"
#include "../libft/includes/libft.h"
#include "../includes/mlx.h"

static int	close_win(void)
{
	exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_mlx	*mlx_info;

	if (argc != 2)
	{
		ft_putendl_fd("The number of arguments must be 2", 2);
		return (0);
	}
	mlx_info = ft_mlx_init();
	mlx_info->map = map_input_parser(argv[1]);
	draw_img(mlx_info);
	mlx_key_hook(mlx_info->win_ptr, key_hook, mlx_info);
	mlx_hook(mlx_info->win_ptr, 17, 0, close_win, mlx_info);
	mlx_loop_hook(mlx_info->mlx_ptr, render_frame, mlx_info);
	mlx_loop(mlx_info->mlx_ptr);
}
