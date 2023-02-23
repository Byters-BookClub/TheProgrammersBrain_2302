/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:50:04 by jonkim            #+#    #+#             */
/*   Updated: 2023/02/24 04:43:06 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_token_list	*new_token_node(char *tok)
{
	t_token_list	*new_token;
	int				toklen;

	new_token = malloc(sizeof(t_token_list));
	if (!new_token)
		return (NULL);
	new_token->token.str = ft_strdup(tok);
	toklen = ft_strlen(tok);
	if (!ft_strncmp(tok, "<", toklen) || !ft_strncmp(tok, "<<", toklen) \
	|| !ft_strncmp(tok, ">>", toklen) || !ft_strncmp(tok, ">", toklen))
		new_token->token.type = REDIRECT;
	else if (!ft_strncmp(tok, "|", toklen))
		new_token->token.type = PIPE;
	else
		new_token->token.type = WORD;
	new_token->next = NULL;
	return (new_token);
}

// 배열로 저장되어있는 내용을 리스트로 변환해준다
// 애초에 리스트로 저장하면 되는거 아닌가?
t_token_list	*make_token_list(char **tokens)
{
	int				i;
	t_token_list	*start;
	t_token_list	*cur;
	t_token_list	*new_token;

	start = ft_calloc(1, sizeof(t_token_list));
	cur = start;
	i = -1;
	while (tokens[++i])
	{
		new_token = new_token_node(tokens[i]);
		cur->next = new_token;
		cur = cur->next;
	}
	double_free(tokens);
		// ? double free는 이미 free 되어있는 대상을 다시 free할 때 쓰는 용어 아닌가
		// 2차원 배열이라서 2번 free해줘야해서 double_free인 것 같긴 함...
		// (추천) double_free -> free_2d_array,
	return (start);
}
