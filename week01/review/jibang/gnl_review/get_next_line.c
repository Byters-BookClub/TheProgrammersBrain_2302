/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:26:36 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/01 23:28:34 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_error	read_buffer_size(t_list **head, t_list *cur, char *str)
{
	cur->rbytes = read(cur->fd, cur->buff, BUFFER_SIZE);
	if (cur->rbytes < 0)
	{
		free_all(head, cur, str);
		return (ERROR);
	}
	cur->offset = 0;
	cur->len = 1;
	return (ERROR_NONE);
}

char	*get_next_line(int fd)
{
	static t_list	*head = FT_NULL;
	t_list			*cur;
	char			*str;

	if (BUFFER_SIZE <= 0 || fd < 0 || get_node(&head, &cur, fd) == ERROR)
		return (FT_NULL);
	str = FT_NULL;
	while (1)
	{
		if (cur->offset == (size_t) cur->rbytes)
			if (read_buffer_size(&head, cur, str) == ERROR)
				return (FT_NULL);
		if (cur->rbytes == 0)
		{
			free_all(&head, cur, FT_NULL);
			return (str);
		}
		if (cur->buff[cur->offset] == '\n')
			return (append_line(&head, cur, &str, WITH_NEW_LINE));
		if (cur->offset == (size_t) cur->rbytes - 1)
			if (!append_line(&head, cur, &str, WITHOUT_NEW_LINE))
				return (FT_NULL);
		cur->offset++;
		cur->len++;
	}
}

/*
comment:
gnl을 t_list라는 구조체에 정보를 담아 관리한 것 같은데 t_error 타입을 만들어서 리턴 시키는 부분이 좋은 것 같음.
책 내용 처럼 chunk로 이해하면 각 fd에 대한 정보를 담는 구조체가 개행까지 읽은 뒤 해당 위치 정보를 계속 저장하는 구조로 while문을 돌면서 개행까지 간다음에
append_line을 호출하면서 개행까지 딱 자른 다음 offset에 해당 위치 저장하고 다음 fd 들어오면 또 진행하는 것으로 이해됨.
개인적으로 쪼금 아쉬운건 append_line 이름 대신에 다른 네이밍을 하면 좀더 직관적이지 않을까 생각했다. 처음에 append_line함수가 어디 라인을 덧붙여주는 느낌의
작명이라 코드를 살펴보기 전에는 좀 헷갈린 부분이 있었음. 또 이름을 t_list 대신에 t_file 같은 좀더 직관적인 이름이었으면 좋았을 것 같다.
*/
