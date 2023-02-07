/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yona <yona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:51:55 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/02 13:22:18 by yona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_INTERNAL_H
# define GET_NEXT_LINE_INTERNAL_H

/*--------------- STANDARD HEADERS ---------------*/

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

/*------------ DEFINE MACRO CONSTANTS ------------*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif

# define NO_CONTENT		0

enum e_success_or_failure {
	SUCCESS = 0,
	FAILURE
};

enum e_status_of_fd {
	NORMAL_FD = 0,
	INVALID_FD,
	EOF_REACHED_FD,
};

enum e_lf_exist_or_not {
	LF_EXIST = true,
	LF_NONE = false
};

/*------------- STRUCT DECLARATIONS --------------*/

typedef struct s_buff
{
	char	str[BUFFER_SIZE];
	int		rbytes;
	int		offset;
	int		lf_idx;
}	t_buff;

typedef struct s_line
{
	char	*str;
	int		len;
}	t_line;

/*-------------- FUNCTION PROTOTYPES -------------*/

int		find_next_lf_idx(t_buff *buf);
void	append_buf_to_line(t_line *line, t_buff *buf, int start, int end);

#endif