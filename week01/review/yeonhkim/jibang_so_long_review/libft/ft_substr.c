/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:41:31 by jibang            #+#    #+#             */
/*   Updated: 2022/03/20 22:10:53 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	full_str_len;
	size_t	size;

	if (s == NULL)
		return (NULL);
	full_str_len = ft_strlen(s);
	if ((size_t)start > full_str_len)
		return (ft_strdup(""));
	size = ft_strlen((char *)s + start);
	if (size < len)
		len = size;
	sub = (char *) malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
