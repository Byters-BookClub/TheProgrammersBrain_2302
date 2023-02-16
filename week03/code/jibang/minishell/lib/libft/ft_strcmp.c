/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:07:15 by yeblee            #+#    #+#             */
/*   Updated: 2022/11/03 02:38:39 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	int				i;
	unsigned char	*u1;
	unsigned char	*u2;

	i = 0;
	u1 = (unsigned char *)str1;
	u2 = (unsigned char *)str2;
	if (!str1 || !str2)
		return (1);
	while (u1[i] || u2[i])
	{
		if (u1[i] != u2[i])
			return ((int)(u1[i] - u2[i]));
		i++;
	}
	return (0);
}
