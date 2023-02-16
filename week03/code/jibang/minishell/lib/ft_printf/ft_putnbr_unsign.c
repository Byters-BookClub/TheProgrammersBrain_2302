/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:26:10 by jibang            #+#    #+#             */
/*   Updated: 2022/06/04 20:52:48 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putnbr_u(unsigned int n, int *len)
{
	char	nb;

	if (n >= 10)
		putnbr_u(n / 10, len);
	nb = '0' + n % 10;
	write(1, &nb, 1);
	*len += 1;
}

void	ft_putnbr_unsign_len(unsigned int n, int *len)
{
	putnbr_u(n, len);
}
