/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:37:09 by cheseo            #+#    #+#             */
/*   Updated: 2022/10/11 13:55:02 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	get_char(t_buffer *buffer)
{
	if (buffer->curr == buffer->end)
	{
		buffer->state = read(buffer->fd, buffer->buf, BUFFER_SIZE);
		buffer->end = buffer->buf + buffer->state;
		buffer->curr = buffer->buf;
	}
	if (buffer->state == ERROR)
		return (0);
	else if (buffer->state == END_OF_FILE)
		return (0);
	return (*(buffer->curr++));
}

char	*get_line(t_string *string)
{
	char	*tmp;

	if (string->len == 0)
		return (NULL);
	tmp = malloc(string->len + 1);
	if (!tmp)
		return (NULL);
	tmp = ft_memcpy(tmp, string->str, string->len);
	tmp[string->len] = '\0';
	return (tmp);
}

char	*append_string(t_string *string, char c)
{
	char	*tmp;

	if (string->len == string->cap)
	{
		tmp = malloc(string->cap << 1);
		if (!tmp)
			return (NULL);
		tmp = ft_memcpy(tmp, string->str, string->len);
		free(string->str);
		string->str = tmp;
		string->cap <<= 1;
	}
	string->str[string->len++] = c;
	return (string->str);
}

char	*read_line(t_buffer **head, t_buffer *buffer, t_string *string)
{
	char	c;

	while (1)
	{
		c = get_char(buffer);
		if (buffer->state == ERROR)
		{
			delete_buffer(head, buffer);
			free(string->str);
			string->str = NULL;
			return (NULL);
		}
		else if (buffer->state == END_OF_FILE)
			break ;
		if (!append_string(string, c))
		{
			delete_buffer(head, buffer);
			free(string->str);
			string->str = NULL;
			return (NULL);
		}
		if (c == '\n')
			break ;
	}
	return (string->str);
}

char	*get_next_line(int fd)
{
	static t_buffer	*head;
	t_buffer		*curr;
	t_string		string;
	char			*res;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	curr = init_buffer(&head, fd);
	if (!curr)
		return (NULL);
	if (!init_string(&string))
	{
		delete_buffer(&head, curr);
		return (NULL);
	}
	if (!read_line(&head, curr, &string))
		return (NULL);
	res = get_line(&string);
	if (!res)
		delete_buffer(&head, curr);
	free(string.str);
	return (res);
}
