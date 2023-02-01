/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:54:33 by jibang            #+#    #+#             */
/*   Updated: 2022/04/08 20:16:53 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_joinlcpy(char *join, char *s, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && s[i])
	{
		join[i] = s[i];
		i++;
	}
	join[i] = '\0';
}

char	*ft_strjoin(char *save, char *buff)
{
	char	*join;
	size_t	len_s;
	size_t	len_b;

	if (save == NULL)
	{
		save = (char *) malloc(sizeof(char) * 1);
		save[0] = '\0';
	}
	if (save == NULL && buff == NULL)
		return (NULL);
	len_s = ft_strlen(save);
	len_b = ft_strlen(buff);
	join = (char *) malloc(sizeof(char) * (len_s + len_b + 1));
	if (!join)
		return (NULL);
	ft_joinlcpy(join, save, len_s + 1);
	ft_joinlcpy(join + len_s, buff, len_b + 1);
	free(save);
	return (join);
}
