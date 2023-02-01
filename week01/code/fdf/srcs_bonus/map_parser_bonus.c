/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:18:31 by dahkang           #+#    #+#             */
/*   Updated: 2022/12/28 19:34:55 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf_bonus.h"
#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line_bonus.h"
#include "../includes/ft_syscalls_bonus.h"

static void	fill_map(int **map_org, int width, int height, char *file_name)
{
	const int	fd = ft_open(file_name, O_RDONLY);
	char		*line;
	char		**strs;
	int			y;
	int			x;

	y = -1;
	while (++y < height)
	{
		x = -1;
		line = get_next_line(fd);
		strs = ft_split(line, ' ');
		if (!strs)
			ft_perror_exit("Failed to split");
		while (++x < width)
			map_org[y][x] = ft_atoi(strs[x]);
		free(line);
		free_strs(strs);
	}
	close(fd);
}

static t_map	*map_init(int width, int height, char *file_name)
{
	t_map	*map;
	int		y;

	map = (t_map *)ft_malloc(sizeof(t_map));
	map = ft_memset(map, 0, sizeof(t_map));
	map->width = width;
	map->height = height;
	if (WIN_WIDTH / map->width < WIN_HEIGHT / map->height)
		map->dist = WIN_WIDTH / map->width / 3;
	else
		map->dist = WIN_HEIGHT / map->height / 3;
	if (map->dist <= 0)
		map->dist = 1;
	map->map_org = (int **)ft_malloc(sizeof(int *) * height);
	y = -1;
	while (++y < height)
		map->map_org[y] = (int *)ft_malloc(sizeof(int) * width);
	fill_map(map->map_org, width, height, file_name);
	return (map);
}

static int	ft_calc_width(char *line)
{
	char	**strs;
	int		width;

	strs = ft_split(line, ' ');
	if (!strs)
		ft_perror_exit("Failed to split");
	width = 0;
	while (strs[width])
		width++;
	if (strs[width - 1][0] == '\n')
		width--;
	free_strs(strs);
	return (width);
}

static void	get_map_size(char *file_name, int *width, int *height)
{
	const int	fd = ft_open(file_name, O_RDONLY);
	char		*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*height == 0)
			*width = ft_calc_width(line);
		else
			if (*width != ft_calc_width(line))
				ft_perror_exit("Map error");
		(*height)++;
		free(line);
	}
	close(fd);
}

t_map	*map_input_parser(char *file_name)
{
	t_map	*map;
	int		width;
	int		height;

	width = 0;
	height = 0;
	get_map_size(file_name, &width, &height);
	if (width == 0 || height == 0)
		ft_err_exit("Empty file", EXIT_FAILURE);
	map = map_init(width, height, file_name);
	return (map);
}
