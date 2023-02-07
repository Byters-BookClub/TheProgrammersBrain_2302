/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:18:31 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/07 17:41:31 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "../includes/fdf.h"
#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line_bonus.h"
#include "../includes/ft_syscalls.h"

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
			map_org[y][x] = ft_atoi(strs[x]); // map에 정보 넣기
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
	if (WIN_WIDTH / map->width < WIN_HEIGHT / map->height) // 높이가 윈도우 대비 비중이 더 크면..
		map->dist = WIN_WIDTH / map->width / 3; // dist는 width / 3....? +,- 에 해당하는 정보인가?
	else
		map->dist = WIN_HEIGHT / map->height / 3;
	if (map->dist <= 0) // 0보다 작게 되면 걍 1로 해준다
		map->dist = 1;
	map->map_org = (int **)ft_malloc(sizeof(int *) * height); // 맵 파싱 지도구나
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

	strs = ft_split(line, ' '); // 스페이스 단위로 스플릿
	if (!strs)
		ft_perror_exit("Failed to split");
	width = 0;
	while (strs[width])
		width++; // 길이 세기
	if (strs[width - 1][0] == '\n')
		width--; // 개행은 빼기
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
		if (*height == 0) // 첫 줄부터 가로 길이 세기
			*width = ft_calc_width(line);
		else
			if (*width != ft_calc_width(line)) // 가로 길이와 현재 문장의 길이가 다르면 에러 처리
				ft_perror_exit("Map error");
		(*height)++; // 줄 수가 맵 높이
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
	if (width == 0 || height == 0) // 에러 처리
		ft_err_exit("Empty file", EXIT_FAILURE);
	map = map_init(width, height, file_name); // 맵 초기화
	return (map);
}
