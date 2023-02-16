/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mem_address_len.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:39:06 by jibang            #+#    #+#             */
/*   Updated: 2022/06/04 21:24:05 by jibang           ###   ########.fr       */
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

void	ft_print_memory(unsigned long long nbr, char *base, int *len)
{
	if (nbr >= (unsigned long long)base_len(base))
	{
		ft_print_memory((nbr / base_len(base)), base, len);
		ft_print_memory((nbr % base_len(base)), base, len);
	}
	else
	{
		write(1, &base[nbr], 1);
		*len += 1;
	}
}

void	ft_print_mem_address_len(unsigned long long nbr, int *len)
{
	ft_putstr_len("0x", len);
	ft_print_memory(nbr, "0123456789abcdef", len);
}
