/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:53:41 by jibang            #+#    #+#             */
/*   Updated: 2022/06/04 20:47:31 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 10

size_t	ft_strlen_gnl(char *s);
void	ft_joinlcpy_gnl(char *join, char *s, size_t size);
int		is_newline(char *save);
char	*ft_strjoin_gnl(char *save, char *buff);
char	*get_remains(char *save);
char	*get_one_line(char *save);
char	*read_newline(int fd, char *save);
char	*get_next_line(int fd);

#endif
