/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:01:52 by jibang            #+#    #+#             */
/*   Updated: 2022/07/05 17:08:31 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_first_line(t_params *var, char *line)
{
	char	*tmp;

	var->map_height = 1;
	var->map_width = ft_strlen(line) - 1;
	tmp = ft_substr(line, 0, var->map_width);
	var->map_line = ft_strdup(tmp);
	var->width_criteria = var->map_width;
	free(tmp);
	free(line);
}

void	get_other_lines(t_params *var, char *line)
{
	char	*tmp;

	var->map_width = ft_strlen(line) - 1;
	if (var->map_width != var->width_criteria)
		ft_perror_exit("wrong map input");
	tmp = ft_substr(line, 0, var->map_width);
	var->map_line = ft_strjoin(var->map_line, tmp);
	free(tmp);
	free(line);
}

int	check_map_line_err(char *line, int width, int height)
{
	int		i;
	int		j;

	i = -1;
	while (++i < width)
	{
		if (line[i] != WALL)
			ft_perror_exit("map error");
	}
	j = 0;
	while (++j < height - 1)
	{
		if (line[i] != WALL || line[i + width - 1] != WALL)
			ft_perror_exit("map error");
		i = i + width;
	}
	while (line[i])
	{
		if (line[i] == '\n')
			return (SUCCESS);
		if (line[i] != WALL)
			ft_perror_exit("map error");
		i++;
	}
	return (SUCCESS);
}

t_params	ft_map_parsing(t_params *var, char **av)
{
	int		fd;
	char	*line;

	// (void)av;
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		ft_perror_exit("map read error");
	line = get_next_line(fd);
	if (line == NULL)
		ft_perror_exit("map read error");
	if (line != NULL)
		get_first_line(var, line);
	while (line != NULL)
	{
		(var->map_height)++;
		line = get_next_line(fd);
		if (line)
			get_other_lines(var, line);
	}
	close(fd);
	check_map_line_err(var->map_line, var->map_width, var->map_height);
	if (check_map_cep(var->map_line) == ERROR)
		ft_perror_exit("Not enough E, C, P");
	var->collect_goal = number_of_collection(var->map_line);
	return (*var);
}

int	check_map_cep(char *line)
{
	int		i;
	int		c_flag;
	int		e_flag;
	int		p_flag;

	i = 0;
	c_flag = 0;
	e_flag = 0;
	p_flag = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			c_flag = 1;
		else if (line[i] == 'E')
			e_flag = 1;
		else if (line[i] == 'P')
			p_flag = 1;
		i++;
	}
	if (c_flag && e_flag && p_flag)
		return (SUCCESS);
	return (ERROR);
}
