/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscalls_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 00:25:04 by dahkang           #+#    #+#             */
/*   Updated: 2022/12/23 01:09:44 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SYSCALLS_BONUS_H
# define FT_SYSCALLS_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

void	ft_perror_exit(char *err_msg);
void	*ft_malloc(size_t size);
int		ft_open(const char *path, int oflag);
void	ft_close(int fd);

#endif
