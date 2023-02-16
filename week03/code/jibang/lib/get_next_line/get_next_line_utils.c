/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:09:13 by yeblee            #+#    #+#             */
/*   Updated: 2022/05/23 17:10:21 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_clear_node(t_gnl_list *node)
{
	free(node->contents);
	node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node);
	node = NULL;
	return (NULL);
}

char	*gnl_append_buff(char const *contents, char const *buff)
{
	char	*ret;

	if (!buff)
		return (NULL);
	ret = malloc(gnl_strlen(contents) + gnl_strlen(buff) + 1);
	if (!ret)
		return (NULL);
	if (!contents)
	{
		gnl_strlcpy(ret, buff, gnl_strlen(buff) + 1);
		return (ret);
	}
	gnl_strlcpy(ret, contents, gnl_strlen(contents) + 1);
	gnl_strlcpy(ret + gnl_strlen(contents), buff, gnl_strlen(buff) + 1);
	return (ret);
}

size_t	gnl_strlen(char const *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	if (!c)
		return ((char *)s + i);
	return (0);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;

	len_src = gnl_strlen(src);
	if (dstsize == 0)
		return (len_src);
	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len_src);
}
