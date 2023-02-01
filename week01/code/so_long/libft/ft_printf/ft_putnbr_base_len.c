/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:29:44 by jibang            #+#    #+#             */
/*   Updated: 2022/06/04 21:24:44 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	base_len(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

void	ft_putnbr_base_len(unsigned int nbr, char *base, int *len)
{
	if (nbr >= base_len(base))
	{
		ft_putnbr_base_len((nbr / base_len(base)), base, len);
		ft_putnbr_base_len((nbr % base_len(base)), base, len);
	}
	else
	{
		write(1, &base[nbr], 1);
		*len += 1;
	}
}
