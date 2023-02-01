/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:56:14 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/01 23:20:16 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FT_NULL (void *) 0

enum e_option
{
	WITHOUT_NEW_LINE,
	WITH_NEW_LINE
};

enum e_error
{
	ERROR_NONE,
	ERROR
};

typedef enum e_error	t_error;

typedef struct s_list
{
	int				fd;
	char			buff[BUFFER_SIZE];
	ssize_t			rbytes;
	size_t			offset;
	size_t			str_len;
	size_t			len;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*append_line(t_list **head, t_list *cur, char **str, int option);
t_error	get_node(t_list **head, t_list **cur, int fd);
void	free_all(t_list **head, t_list *cur, char *str);

#endif