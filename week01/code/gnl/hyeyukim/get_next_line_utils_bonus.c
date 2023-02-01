/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:56:23 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/01 23:29:10 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*create_node(int fd)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (FT_NULL);
	new->fd = fd;
	new->rbytes = 0;
	new->offset = 0;
	new->str_len = 0;
	new->len = 1;
	new->next = FT_NULL;
	return (new);
}

t_error	get_node(t_list **head, t_list **cur, int fd)
{
	*cur = *head;
	while (*cur)
	{
		if ((*cur)->fd == fd)
			return (ERROR_NONE);
		*cur = (*cur)->next;
	}
	*cur = create_node(fd);
	if (!*cur)
		return (ERROR);
	(*cur)->next = *head;
	*head = *cur;
	return (ERROR_NONE);
}

void	free_all(t_list **head, t_list *cur, char *str)
{
	t_list	*tem;

	free(str);
	if (*head == cur)
	{
		*head = cur->next;
	}
	else
	{
		tem = *head;
		while (tem->next != cur)
		{
			tem = tem->next;
		}
		tem->next = cur->next;
	}
	free(cur);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && dstsize && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*append_line(t_list **head, t_list *cur, char **str, int option)
{
	char	*new;

	new = malloc(cur->str_len + cur->len + 1);
	if (!new)
	{
		free_all(head, cur, *str);
		return (FT_NULL);
	}
	if (*str)
	{
		ft_strlcpy(new, *str, cur->str_len + 1);
		free(*str);
	}
	ft_strlcpy(new + cur->str_len, \
				&cur->buff[1 + cur->offset - cur->len], cur->len + 1);
	cur->str_len += cur->len;
	cur->len = 1;
	if (option == WITH_NEW_LINE)
	{
		cur->str_len = 0;
		cur->offset++;
	}
	*str = new;
	return (new);
}
