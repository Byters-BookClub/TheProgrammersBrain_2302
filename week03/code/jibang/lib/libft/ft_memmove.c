/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:59:34 by jibang            #+#    #+#             */
/*   Updated: 2022/03/19 14:49:42 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s = src;
	unsigned char		*d;
	size_t				i;
	size_t				size;

	d = (unsigned char *) dst;
	if (s - d < 0)
	{
		size = len;
		while (size--)
			d[size] = s[size];
	}
	if (s - d > 0)
	{
		i = -1;
		size = len;
		while (++i < size)
			d[i] = s[i];
	}
	return ((void *)d);
}
