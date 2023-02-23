/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:59:30 by jonkim            #+#    #+#             */
/*   Updated: 2023/02/24 04:33:09 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

static	int	token_check(char *str, char **tokens, int *i, int *j)
{
	int	tmp;

	while (str[*i] == ' ')
		(*i)++;
		// 공백 밀어주기
	tmp = *i;
		// 일단 tmp 초기화
	if (str[*i] == '|')
	{
		tokens[(*j)++] = ft_strdup("|");
		(*i)++;
		tmp++;
	}
		// 파이프 나오면 tokens에 파이프 토큰 저장해주고 i 밀어줌
	if (str[*i] == '<' || str[*i] == '>')
	{
		redirection(str, i);
		tokens[(*j)++] = ft_substr(str, tmp, (*i) - tmp);
		tmp = *i;
	}
		// 리다이렉션 나오면 그만큼 밀어주고 리다이렉션 기호 나온 부분 전체를 토큰으로 저장해줌
	return (tmp); // tmp 반환해주기... 왜...?
}

char	**make_token(char *str, char **tokens)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		tmp = token_check(str, tokens, &i, &j);
			// 무엇을 확인하는지 더 구체적으로 설명하면 좋을 것 같다.
			// 무엇인지는 모르겠지만 str에서 토큰을 추출해서 tokens에 저장하는듯?
			// 반환값은 int형인 것 같은데 token 확인해서 무엇을 반환하는걸까
		// quote 맞는 쌍 나 올때까지 밀어주기
		if (str[i] == '\'' || str[i] == '\"')
			quote(str, &i, str[i]);
		// word 밀어주기
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' \
		&& str[i] != '|' && str[i] != '>' && str[i] != '<')
			word(str, &i);
		if (i != tmp) // i랑 tmp 값을 비교하네... token_check 함수를 확인해야 뭔지 알 것 같다.
			tokens[j++] = ft_substr(str, tmp, i - tmp);
			// tmp 왜 반환하나 했더니 word 때문이구마잉
	}
	tokens[token_count(str)] = 0; 
		//? 여기서 token_count 함수를 다시 호출하네
		// 벌써 3번째인 것 같은데...
		// 그냥 아까 tokenize 함수에서 token_count(함수 이름은 count_tokenS이었으면 좋았을듯) 호출했을 때 결과값을 변수(count)에 저장해놨다가
		// tokens 할당했을 때 바로 tokens[count] = 0 이렇게 미리 초기화해놨으면 좋았을듯
	return (tokens);
}
