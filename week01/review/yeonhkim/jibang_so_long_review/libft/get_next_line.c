/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:52:58 by jibang            #+#    #+#             */
/*   Updated: 2022/06/25 19:53:48 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line/get_next_line.h"
#include "libft.h"

int	is_newline(char *save)
{
	int		i;

	if (save == NULL)
		return (0);
	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_remains(char *save)
{
	char	*remains;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	len = ft_strlen_gnl(save);
	remains = (char *) malloc(sizeof(char) * (len - (i + 1) + 1));
	if (!remains)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		remains[j++] = save[i++];
	remains[j] = '\0';
	free(save);
	return (remains);
}

char	*get_one_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (save[i] == '\0')
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *) malloc(sizeof(char) * (i + 1 + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_newline(int fd, char *save)
{
	char	*buff;
	int		read_idx;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_idx = 1;
	while (!is_newline(save) && read_idx != 0)
	{
		read_idx = read(fd, buff, BUFFER_SIZE);
		if (read_idx == 0)
			return (NULL);
		if (read_idx == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_idx] = '\0';
		save = ft_strjoin_gnl(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_newline(fd, save);
	if (!save)
		return (NULL);
	line = get_one_line(save);
	save = get_remains(save);
	return (line);
}
