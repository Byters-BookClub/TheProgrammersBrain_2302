/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:12:03 by dahkang           #+#    #+#             */
/*   Updated: 2022/12/27 04:12:28 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_strs(char *strs[])
{
	int	i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}
