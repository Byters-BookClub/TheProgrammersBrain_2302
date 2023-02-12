/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:17:35 by jibang            #+#    #+#             */
/*   Updated: 2023/02/06 21:45:33 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// 아마 ft_put_images 외의 함수들은 외부에서 호출하지 않는 함수들 같은데 static으로 두는 것이 좋았을 것 같다.

void	put_info(t_params var)
{
	t_string	str;
	// 이 함수 내부에서만 사용하는, 서로 관련이 있다고는 보기 힘든 변수들이라
	// 굳이 구조체로 묶어둘 필요는 없었을 것 같은데, 혹시 25줄 이내로 맞추시려고 그런걸까?
	// char	*strs[3];
	// strs[STR_STEP];
	int			x;
	int			y;
	int			x1;	// x1이 뭐지? 아는 전자기기 모델명이 x1이긴한데 그건 아닐테고....

	str.col = ft_itoa(var.collect_now);
	str.mis = ft_itoa(var.collect_goal);
	str.step = ft_itoa(var.step);
	x = DOTS / 6;			// DOTS가 대체 뭘까? 왜 파일 6으로 나눌까?
	y = DOTS / 4;			// 왜 하필 4로?
	x1 = 5 * DOTS / 7;		// 왜 파일 7 나누고 5 곱하기를??

	// 0x00을 COLOR_BLACK과 같은 이름의 매크로 상수로 지정해두고 사용했으면 좋았을 듯
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

// WALL, C, E를 decoration이라고 칭하는 거였구나.
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

// 함수명이 재밌다.
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


// put_images 함수가 내부적으로 put_() 함수들을 호출하고 있는 것이 깔끔해서 보기 좋다.
void	ft_put_images(t_params var)
{
	t_image		img;
	int			w;
	int			h;

	if (check_e_finished(var) == TRUE)	// put_images 함수가 game의 finish 여부를 판별하네???? 뭐지?
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
