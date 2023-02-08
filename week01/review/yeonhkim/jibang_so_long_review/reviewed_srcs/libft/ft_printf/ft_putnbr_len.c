/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:20:37 by jibang            #+#    #+#             */
/*   Updated: 2022/06/04 20:51:37 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putnbr(int n, int *len)
{
	char	nb;

	if (n >= 10)
		putnbr(n / 10, len);
	nb = '0' + n % 10;
	write(1, &nb, 1);
	*len += 1;
}

void	ft_putnbr_len(int n, int *len)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*len += 11;
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
		*len += 1;
	}
	putnbr(n, len);
}
