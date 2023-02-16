/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:14:58 by jibang            #+#    #+#             */
/*   Updated: 2022/03/19 20:06:06 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	get_num_size(long long n)
{
	long long	size;

	size = 0;
	if (n < 9)
		return (1);
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static long long	my_abs(long long n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}

char	*ft_itoa(int n)
{
	char		*num;
	long long	num_size;
	long long	sign;
	long long	nb;

	sign = 0;
	if (n < 0)
		sign = 1;
	nb = my_abs((long long)n);
	num_size = get_num_size(nb);
	if (sign)
		num_size += 1;
	num = (char *) malloc(sizeof(char) * (num_size + 1));
	if (!num)
		return (NULL);
	num[num_size] = '\0';
	while (num_size)
	{
		num[num_size-- - 1] = '0' + nb % 10;
		nb /= 10;
	}
	if (sign)
		num[0] = '-';
	return (num);
}
