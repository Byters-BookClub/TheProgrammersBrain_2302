/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:35:47 by jibang            #+#    #+#             */
/*   Updated: 2022/03/20 22:53:46 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	hay_size;
	size_t	needle_size;
	size_t	count_index;

	if (needle[0] == '\0')
		return ((char *)haystack);
	hay_size = ft_strlen(haystack);
	needle_size = ft_strlen(needle);
	if (hay_size < needle_size || len < needle_size)
		return (NULL);
	count_index = 0;
	if (len <= hay_size)
		count_index = len - needle_size;
	if (len > hay_size)
		count_index = hay_size - needle_size;
	i = 0;
	while (i <= count_index)
	{
		if (ft_strncmp(haystack + i, needle, needle_size) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
