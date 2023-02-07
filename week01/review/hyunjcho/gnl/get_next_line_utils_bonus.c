/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:56:23 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/07 17:39:42 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*create_node(int fd)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (FT_NULL);
	// 구조체 초기화
	new->fd = fd;
	new->rbytes = 0;
	new->offset = 0;
	new->str_len = 0;
	new->len = 1;
	new->next = FT_NULL;
	return (new);
}

t_error	get_node(t_list **head, t_list **cur, int fd)
{
	*cur = *head;
	while (*cur) // 노드가 존재하는 동안 반복
	{
		if ((*cur)->fd == fd) // 들어온 fd를 찾으면 정상 리턴
			return (ERROR_NONE);
		*cur = (*cur)->next; // 다음 노드 탐색
	}
	*cur = create_node(fd); // 해당 fd를 가진 노드가 없을 경우 노드 생성
	if (!*cur) // 에러 반환
		return (ERROR);
	(*cur)->next = *head; // 다음 노드 헤드로 연결
	*head = *cur; // 헤드를 방금 만든 노드로 함, 새로 만든 노드가 헤드가 돼서 점점 앞에 붙여짐 뒤가 아니라
	// (*cur)->next = create_node(fd);로 만들지 않은 것은 따로 첫노드인지 검사를 하지 않기 위함인가?
	// 이게 if 조건문으로 하는 것보다 연산 속도는 좋을 수도?
	return (ERROR_NONE);
}

void	free_all(t_list **head, t_list *cur, char *str)
{
	t_list	*tem;

	free(str);
	if (*head == cur)
	{
		*head = cur->next;
	}
	else
	{
		tem = *head;
		while (tem->next != cur)
		{
			tem = tem->next;
		}
		tem->next = cur->next;
	}
	free(cur);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && dstsize && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*append_line(t_list **head, t_list *cur, char **str, int option)
{
	char	*new;

	new = malloc(cur->str_len + cur->len + 1); // 가지고 있는 문장 + 붙일 문장 길이만큼 할당
	if (!new) // 에러 처리
	{
		free_all(head, cur, *str);
		return (FT_NULL);
	}
	if (*str) // 문장에 뭔가 남아 있으면 뉴에 넣어주기
	{
		ft_strlcpy(new, *str, cur->str_len + 1);
		free(*str);
	}
	ft_strlcpy(new + cur->str_len, \
				&cur->buff[1 + cur->offset - cur->len], cur->len + 1); // str 뒤에 붙일 문장 붙이기
	// 이부분 그냥 strjoin으로 한꺼번에 처리해줘도 괜찮지 않았을지?
	cur->str_len += cur->len; // 반환하지 않고 담고있는 문장 길이
	cur->len = 1; // 다음 가져올 문장 길이 초기화
	if (option == WITH_NEW_LINE) // 개행이 있을 경우 다음 탐색을 위해 초기화
	{
		cur->str_len = 0;
		cur->offset++;
	}
	*str = new; // 반환하지 않는 경우 합칠 수 있도록
	// cur->str_len += cur_len; && *str = new;은 개행이 있는 경우 의미없는 연산이므로 if문 안에서 return을 하고
	// 아닐 경우 진행을 했어도 괜찮았을 느낌?
	/**
	 cur->len = 1;
	 if (option == WITH_NEW_LINE) {
		cur->str_len = 0;
		cur->offset++;
		return(new);
	 }
	 cur->str_len += cur_len;
	 *str = new;
	 return (str); 같이?
	 */
	return (new);
}
