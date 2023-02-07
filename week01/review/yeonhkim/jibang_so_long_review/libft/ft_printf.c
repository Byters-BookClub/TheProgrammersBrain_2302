/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:35:59 by jibang            #+#    #+#             */
/*   Updated: 2022/06/04 20:58:15 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include "libft.h"

void	ft_flag(va_list ap, char flag, int *len)
{
	if (flag == 's')
		ft_putstr_len(va_arg(ap, char *), len);
	else if (flag == 'c')
		ft_putchar_len(va_arg(ap, int), len);
	else if (flag == 'd' || flag == 'i')
		ft_putnbr_len(va_arg(ap, int), len);
	else if (flag == 'u')
		ft_putnbr_unsign_len(va_arg(ap, unsigned int), len);
	else if (flag == 'x')
		ft_putnbr_base_len(va_arg(ap, unsigned int), "0123456789abcdef", len);
	else if (flag == 'X')
		ft_putnbr_base_len(va_arg(ap, unsigned int), "0123456789ABCDEF", len);
	else if (flag == 'p')
		ft_print_mem_address_len((unsigned long long)va_arg(ap, void *), len);
	else if (flag == '%')
		ft_putchar_len('%', len);
}

int	ft_parse(va_list ap, char *str, int *len)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
			ft_putchar_len(str[i], len);
		else if (str[i] == '%' && str[i + 1] != '\0')
		{
			ft_flag(ap, str[i + 1], len);
			i++;
		}
		i++;
	}
	return (*len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, str);
	len = ft_parse(ap, (char *)str, &len);
	va_end(ap);
	return (len);
}
