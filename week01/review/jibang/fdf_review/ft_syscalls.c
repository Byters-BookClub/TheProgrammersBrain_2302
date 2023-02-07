/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscalls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 23:48:07 by dahkang           #+#    #+#             */
/*   Updated: 2022/12/22 21:24:58 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_syscalls.h"

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		ft_perror_exit("malloc failed");
	return (ret);
}

int	ft_open(const char *path, int oflag)
{
	int	fd;

	fd = open(path, oflag);
	if (fd < 0)
		ft_perror_exit("Failed to open file");
	return (fd);
}

void	ft_close(int fd)
{
	if (close(fd) < 0)
		ft_perror_exit("Failed to close file");
}
