/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:54:28 by cheseo            #+#    #+#             */
/*   Updated: 2022/10/11 15:24:15 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tmp;
	unsigned char const	*str;

	i = 0;
	tmp = (unsigned char *)dst;
	str = (unsigned char const *)src;
	if (!n || dst == src)
		return (dst);
	while (i < n)
	{
		tmp[i] = str[i];
		i++;
	}
	return (dst);
}

t_buffer	*init_buffer(t_buffer **head, int fd)
{
	t_buffer	*prev;
	t_buffer	*new;

	prev = NULL;
	while (*head && (*head)->fd != fd)
	{
		prev = *head;
		head = &((*head)->next);
	}
	if (*head)
		return (*head);
	new = ft_calloc(1, sizeof(t_buffer));
	if (!new)
		return (NULL);
	new->fd = fd;
	*head = new;
	new->prev = prev;
	if (prev)
		prev->next = new;
	return (new);
}

char	*init_string(t_string *string)
{
	string->str = malloc(1);
	if (!string->str)
		return (NULL);
	string->len = 0;
	string->cap = 1;
	return (string->str);
}

void	delete_buffer(t_buffer **head, t_buffer *buffer)
{
	if (buffer->next)
		buffer->next->prev = buffer->prev;
	if (buffer->prev)
		buffer->prev->next = buffer->next;
	if (*head == buffer)
		*head = buffer->next;
	free(buffer);
	buffer = NULL;
}
