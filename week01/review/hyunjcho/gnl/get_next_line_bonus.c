/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:56:03 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/07 17:37:35 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_error	read_buffer_size(t_list **head, t_list *cur, char *str)
{
	cur->rbytes = read(cur->fd, cur->buff, BUFFER_SIZE); // 읽기
	if (cur->rbytes < 0) // 읽기 실패 에러 처리
	{
		free_all(head, cur, str); 
		return (ERROR);
	}
	cur->offset = 0; // offset 초기화
	cur->len = 1; // 길이 초기화
	return (ERROR_NONE);
}

char	*get_next_line(int fd)
{
	static t_list	*head = FT_NULL;
	t_list			*cur;
	char			*str;

	if (BUFFER_SIZE <= 0 || fd < 0 || get_node(&head, &cur, fd) == ERROR)
	// 에러 처리: buffer_size 음수, fd 음수, 연결리스트가 제대로 만들어지지 않았을 때(기존 항목들 프리 안해줘도 되나?)
		return (FT_NULL);
	str = FT_NULL;
	while (1)
	{
		if (cur->offset == (size_t) cur->rbytes) // 탐색한 인덱스가 문장의 끝('\0')일 경우
			if (read_buffer_size(&head, cur, str) == ERROR)
				return (FT_NULL);
		if (cur->rbytes == 0) // 읽은 게 없으면 리턴. 읽기 끝
		{
			free_all(&head, cur, FT_NULL);
			return (str);
		}
		if (cur->buff[cur->offset] == '\n') // 읽은 문장에서 개행을 찾은 경우, 이부분 strchr 같은 함수로 따로 빼서 돌리는 게 낫지 않았을까? 전체 while문 내의 if 문을 글자하나하나 다 보게되니까
			return (append_line(&head, cur, &str, WITH_NEW_LINE));
		if (cur->offset == (size_t) cur->rbytes - 1) // 읽은 문장 끝까지 개행이 없는 경우
			if (!append_line(&head, cur, &str, WITHOUT_NEW_LINE)) // 에러가 있을 경우만 리턴, 아닐 경우 다음 read 실행
				return (FT_NULL);
		cur->offset++; // 개행 이후 탐색할 수 있도록 초기화
		cur->len++; // 길이 1로 초기화
	}
}
