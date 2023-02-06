/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:20:04 by jibang            #+#    #+#             */
/*   Updated: 2022/06/04 20:48:15 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_putchar_len(char c, int *len);
void	ft_putstr_len(char *s, int *len);
void	ft_putnbr_len(int n, int *len);
void	ft_putnbr_unsign_len(unsigned int n, int *len);
void	ft_putnbr_base_len(unsigned int nbr, char *base, int *len);
void	ft_print_mem_address_len(unsigned long long nbr, int *len);
int		ft_printf(const char *str, ...);

#endif
