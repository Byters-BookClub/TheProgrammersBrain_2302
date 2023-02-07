/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:56:14 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 18:30:38 by hyunjcho         ###   ########.fr       */
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

typedef struct s_list // 한 번에 읽은만큼 저장하는 연결리스트
{
	int				fd; // 읽을 fd
	char			buff[BUFFER_SIZE]; // 읽은 거 담을 버퍼
	ssize_t			rbytes; // 읽은 바이트 수 기록?
	size_t			offset; // 어펜드 시점 마지막 인덱스
	size_t			str_len; // 해당 리스트에 저장하고 있는 문장 길이?
	size_t			len; // 어펜드 시점 문장 길이
	struct s_list	*next; // 다음 리스트 포인터
}	t_list;

char	*get_next_line(int fd);
char	*append_line(t_list **head, t_list *cur, char **str, int option); 
t_error	get_node(t_list **head, t_list **cur, int fd);
void	free_all(t_list **head, t_list *cur, char *str);

#endif