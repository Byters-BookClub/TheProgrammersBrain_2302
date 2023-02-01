/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:53:41 by jibang            #+#    #+#             */
/*   Updated: 2022/04/08 20:16:34 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

size_t	ft_strlen(char *s);
void	ft_joinlcpy(char *join, char *s, size_t size);
int		is_newline(char *save);
char	*ft_strjoin(char *save, char *buff);
char	*get_remains(char *save);
char	*get_one_line(char *save);
char	*read_newline(int fd, char *save);
char	*get_next_line(int fd);

#endif
