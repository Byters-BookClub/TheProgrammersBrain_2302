/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:54:22 by cheseo            #+#    #+#             */
/*   Updated: 2022/10/11 12:34:05 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buffer	t_buffer;
typedef struct s_string	t_string;

struct	s_buffer
{
	int			fd;
	int			state;
	char		buf[BUFFER_SIZE];
	char		*curr;
	char		*end;
	t_buffer	*prev;
	t_buffer	*next;
};

struct	s_string
{
	char	*str;
	int		len;
	int		cap;
};

enum	e_file_state
{
	ERROR = -1,
	END_OF_FILE
};

char		get_char(t_buffer *buffer);
char		*get_line(t_string *string);
char		*append_string(t_string *string, char c);
char		*read_line(t_buffer **head, t_buffer *buffer, t_string *string);
char		*get_next_line(int fd);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
t_buffer	*init_buffer(t_buffer **head, int fd);
char		*init_string(t_string *string);
void		delete_buffer(t_buffer **head, t_buffer *buffer);

#endif