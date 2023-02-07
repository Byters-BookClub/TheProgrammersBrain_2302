/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:36:03 by jibang            #+#    #+#             */
/*   Updated: 2022/03/18 18:20:27 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	u;
	unsigned char	*mem;

	u = (unsigned char) c;
	mem = (unsigned char *) b;
	while (len--)
		mem[len] = u;
	return ((void *)mem);
}
