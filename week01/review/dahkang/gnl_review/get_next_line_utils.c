/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yona <yona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 02:32:37 by yona              #+#    #+#             */
/*   Updated: 2023/02/02 13:32:15 by yona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_internal.h"

static void	ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

int	find_next_lf_idx(t_buff *buf)
{
	int	idx;

	idx = buf->offset;
	while (idx < buf->rbytes)
	{
		if (buf->str[idx] == '\n')
		{
			buf->lf_idx = idx;
			return (SUCCESS);
		}
		idx++;
	}
	buf->lf_idx = -1;
	return (FAILURE);
}

void	append_buf_to_line(t_line *line, t_buff *buf, int start, int end)
{
	char	*newline;

	if (start > end)
		return ;
	newline = malloc(sizeof(char) * (line->len + (end - start + 1) + 1));
	if (!newline)
		return ;
	ft_strncpy(newline, line->str, line->len);
	ft_strncpy(&newline[line->len], &buf->str[start], (end - start) + 1);
	free(line->str);
	line->str = newline;
	line->len += (end - start + 1);
	buf->offset = (end + 1);
}
