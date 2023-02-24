/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:33:23 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/23 23:20:15 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer_internal.h"

static int	count_tokens(const char *input)
{
	int	cnt;
	int	cur_token_type;
	int	cur_word_length;

	cnt = 0;
	while (*input)
	{
		while (is_blank(*input)) // 우선 블랭크로 구분
			input++;
		cur_token_type = get_token_type(input);
		if (cur_token_type == TOKEN_NONE)
			break ;
		else if (cur_token_type == TOKEN_WORD)
		{
			cur_word_length = length_of_word(input); // 여기서 따옴표 등 다시 처리, 그만큼 포인터 이동
			if (cur_word_length < 0)
				return (-1);
			input += cur_word_length;
		}
		else
			input += length_of_operator(cur_token_type); // && || << >> < > 처리..그만큼 포인터 이동
		cnt++;
	}
	return (cnt);
}

static int	do_lexing(char *input, t_token *token_list, int token_cnt) // 토큰리스트에 실제적으로 추가해주는 함수
{
	int	i;
	int	cur_token_type;

	i = 0;
	while (i < token_cnt)
	{
		while (is_blank(*input))
			input++;
		cur_token_type = get_token_type(input); // count_tokens() 때 했던 일의 일부분을 반복해서 token 타입 뽑아내는군
		if (cur_token_type == TOKEN_WORD)
		{
			token_list[i] = extract_word_token(&input);
			if (!token_list[i].str)
			{
				token_list[i].type = TOKEN_NONE;
				return (FAILURE);
			}
		}
		else
			token_list[i] = extract_operator_token(&input, cur_token_type);
		i++;
	}
	token_list[token_cnt].type = TOKEN_NONE; //마지막은 TOKEN_NONE으로 가리키는 구나..
	return (SUCCESS);
}

int	lexer(char *input, t_token **token_list)
{
	int		token_cnt;

	token_cnt = count_tokens(input); // 토큰으로 구분해서 몇개인지 세겠구나
	if (token_cnt == -1)
	{
		handle_syntax_error((t_token){TOKEN_NONE, NULL});
		return (FAILURE);
	}
	*token_list = malloc(sizeof(t_token) * (token_cnt + 1)); // 개수만큼 malloc
	if (!*token_list || do_lexing(input, *token_list, token_cnt) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
