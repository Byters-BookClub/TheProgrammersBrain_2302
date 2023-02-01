/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:56:03 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/01 23:28:54 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_error	read_buffer_size(t_list **head, t_list *cur, char *str)
{
	cur->rbytes = read(cur->fd, cur->buff, BUFFER_SIZE);
	if (cur->rbytes < 0)
	{
		free_all(head, cur, str);
		return (ERROR);
	}
	cur->offset = 0;
	cur->len = 1;
	return (ERROR_NONE);
}

char	*get_next_line(int fd)
{
	static t_list	*head = FT_NULL;
	t_list			*cur;
	char			*str;

	if (BUFFER_SIZE <= 0 || fd < 0 || get_node(&head, &cur, fd) == ERROR)
		return (FT_NULL);
	str = FT_NULL;
	while (1)
	{
		if (cur->offset == (size_t) cur->rbytes)
			if (read_buffer_size(&head, cur, str) == ERROR)
				return (FT_NULL);
		if (cur->rbytes == 0)
		{
			free_all(&head, cur, FT_NULL);
			return (str);
		}
		if (cur->buff[cur->offset] == '\n')
			return (append_line(&head, cur, &str, WITH_NEW_LINE));
		if (cur->offset == (size_t) cur->rbytes - 1)
			if (!append_line(&head, cur, &str, WITHOUT_NEW_LINE))
				return (FT_NULL);
		cur->offset++;
		cur->len++;
	}
}
