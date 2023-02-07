/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 00:49:55 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/07 17:54:03 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx.h"
#include "../includes/fdf.h"
#include "../includes/ft_syscalls.h"
#include "../libft/includes/libft.h"

static void	my_put_pixel(int x, int y, t_mlx *mlx_info)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = mlx_info->img_addr + (y * mlx_info->size_l + x * (mlx_info->bpp / 8));
	*(unsigned int *)dst = 0x00FFFFFF;
}

static void	plot_line2(t_point *p1, t_point *p2, t_aider *aid, t_mlx *mlx_info)
{
	aid->err[0] = aid->dx + aid->dy; // 왜 또 한 번 계산하지?
	while (1)
	{
		my_put_pixel(p1->x, p1->y, mlx_info);
		if (p1->x == p2->x && p1->y == p2->y)
			break ;
		aid->err[1] = 2 * aid->err[0];
		if (aid->err[1] >= aid->dy)
		{
			if (p1->x == p2->x)
				break ;
			aid->err[0] += aid->dy;
			p1->x += aid->sx;
		}
		if (aid->err[1] <= aid->dx)
		{
			if (p1->y == p2->y)
				break ;
			aid->err[0] += aid->dx;
			p1->y += aid->sy;
		}
	}
}

static void	plot_line(t_point p1, t_point p2, t_mlx *mlx_info) // 선 그리기..?
{
	t_aider	aid;
	int		mask[2];

	aid.dx = ft_abs(p1.x - p2.x); // 점 2개 사이의 거리로 뭔가 하는 듯..
	aid.dy = -ft_abs(p1.y - p2.y);
	aid.sx = 2 * (p1.x < p2.x) - 1; // 뭘 위한 계산인지 모르겠음..
	aid.sy = 2 * (p1.y < p2.y) - 1;
	aid.err[0] = aid.dx + aid.dy; // 에러 ?!
	mask[0] = (p1.y < 0) << 3 | (p1.y >= WIN_HEIGHT) << 2 // 마스크?!
		| (p1.x >= WIN_WIDTH) << 1 | (p1.x < 0);
	mask[1] = (p2.y < 0) << 3 | (p2.y >= WIN_HEIGHT) << 2
		| (p2.x >= WIN_WIDTH) << 1 | (p2.x < 0);
	if ((mask[0] & mask[1]) != 0)
		return ;
	plot_line2(&p1, &p2, &aid, mlx_info); // 2???
}

static t_point	transform(int x, int y, t_mlx *mlx_info)
{
	t_map *const	map = mlx_info->map;
	t_vars *const	vars = mlx_info->vars;
	t_vertex		v;
	t_point			p;

	vars->px_scale = RATIO * vars->px_scale + (1 - RATIO) * vars->x_scale;
	vars->py_scale = RATIO * vars->py_scale + (1 - RATIO) * vars->y_scale;
	vars->pz_scale = RATIO * vars->pz_scale + (1 - RATIO) * vars->z_scale;
	v.x = x * map->dist * vars->px_scale;
	v.y = y * map->dist * vars->py_scale;
	v.z = map->map_org[y][x] * map->dist * vars->pz_scale;
	rotate_x(&v, vars->alpha); // 변경값으로 다 회전
	rotate_y(&v, vars->beta);
	rotate_z(&v, vars->gamma);
	v.x += vars->x_translate + WIN_WIDTH / 2.0;
	v.y += vars->y_translate + WIN_HEIGHT / 2.0;
	p.x = lround(v.x);
	p.y = lround(v.y);
	p.z = lround(v.z);
	return (p);
}

int	draw_img(t_mlx *mlx_info)
{
	int	y;
	int	x;

	set_mlx_img(mlx_info);
	y = -1;
	while (++y < mlx_info->map->height)
	{
		x = -1;
		while (++x < mlx_info->map->width)
		{
			if (x < mlx_info->map->width - 1) // x축에 관 한 건지 y축에 관한건지 검사?
				plot_line(transform(x, y, mlx_info), \
						transform(x + 1, y, mlx_info), mlx_info);
			if (y < mlx_info->map->height - 1)
				plot_line(transform(x, y, mlx_info), \
						transform(x, y + 1, mlx_info), mlx_info);
		}
	}
	mlx_put_image_to_window(mlx_info->mlx_ptr, mlx_info->win_ptr, \
							mlx_info->img_ptr, 0, 0);
	return (1);
}
