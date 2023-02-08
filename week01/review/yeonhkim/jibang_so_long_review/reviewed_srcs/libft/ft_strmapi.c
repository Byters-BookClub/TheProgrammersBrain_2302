/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:22:07 by jibang            #+#    #+#             */
/*   Updated: 2022/03/19 19:06:24 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*pstr;
	unsigned int	len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	len = (unsigned int) ft_strlen(s);
	pstr = (char *) malloc(sizeof(char) * (len + 1));
	if (!pstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		pstr[i] = f(i, s[i]);
		i++;
	}
	pstr[len] = '\0';
	return (pstr);
}
