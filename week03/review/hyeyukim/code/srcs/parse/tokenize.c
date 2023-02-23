/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:50:16 by jonkim            #+#    #+#             */
/*   Updated: 2023/02/24 04:29:53 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	quote(char *str, int *i, char c)
{
	int	tmp;

	tmp = *i;
	while (str[++(*i)])
	{
		if (str[*i] == c)
		{
			(*i)++;
			return ;
		}
	}
	*i = tmp + 1;
}

void	word(char *str, int *i)
{
	if (!str[*i])
		return ;
	// 어차피 '\0'이면 아래 while 순회 못하니까 굳이 조건문으로 확인하지 않아도 될 것 같음
	while (str[(*i)])
	{
		if (str[*i] == ' ' || str[*i] == '|' || \
		str[*i] == '>' || str[*i] == '<')
			return ;
		if (str[*i] == '\'' || str[*i] == '\"')
			quote(str, i, str[*i]);
		(*i)++;
	}
}

void	redirection(char *str, int *i)
{
	if (str[(*i) + 1] == str[*i])
		(*i)++;
	(*i)++;
}

// token count는 명사인데 함수명은 동사로 표현하는게 더 가독성이 좋은 것 같다
// count_token은 어떨까
int	token_count(char *str)
{
	int	ret;
	// return의 줄임말인가...? 아 result의 줄임말이구만
	// 뭔가 res가 더 편하긴 한데 이건 갠취일수도...? 
	// 그런데 이 함수는 토큰 개수를 반환하는 함수니까 그냥 count라고 하는 것도 괜찮았을듯?
	int	i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		// 파이프~
		if (str[i] == '|')
		{
			ret++;
			i++;
		}
		// 리다이렉션~
		if (str[i] == '<' || str[i] == '>')
			redirection(str, &i);
				// 흐음... 근데 redirection은 뭘까.
				// 아 redirection 나온 부분만큼 i를 늘려주는 거구나
				// 그냥 redirection이라고 하면 파악하기 어려우니까
				// pass_redirection과 같이 무슨 일을 하는 함수인지 드러나게 짜면 좋을듯
				// 그런데 사실 그냥 함수로 뺄 필요도 없이 그냥 i++하면 되는거 아닌가?
				// 아 <<, <, >>, >를 모두 하나의 토큰 타입으로 묶었구나
		// 쿼트~
		if (str[i] == '\'' || str[i] == '\"')
			quote(str, &i, str[i]);
			// redirection과 동일하게 pass_quote가 낫지 않았을까
		// 워드~
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && \
		str[i] != '|' && str[i] != '>' && str[i] != '<')
			word(str, &i);
			// redirection과 동일하게 pass_word
		// 공백 다 밀어주기~
		while (str[i] == ' ')
			i++;
		ret++;
			// 오 ret++를 맨 밑에 둬서 한 번에 처리했구나
			// 저 파이프만 ret++를 한 번 더 하네
			// 흠... 왜지
			// 아 애초에 else if 문이 아니라 그냥 if문이구나
			// 그럼 >'"'word 이런 친구는 하나의 토큰으로 취급하는건가
			// 구조체를 확인해보니 REDIRECT, PIPE, PIPELINE, WORD 이렇게 나눠져있었는데  
			// 이러면 토큰 두 개 아닌가. 띠롱?
	}
	return (ret);
}

char	**tokenize(char *str)
{
	char	**tokens;

		// 토큰 개수 세기~
	if (token_count(str) == 0)
		return (NULL);
		// 할당해주기~
	tokens = ft_calloc((token_count(str) + 1), sizeof(char *));
		// 오... token_count를 또 부르네?
		// 그냥 변수 하나 정의해서 거기에다가 token_count 반환값을 저장해줬다면 좋았을 것 같다.
	if (!tokens)
		return (NULL); 
		// 엥? 이때까지 할당하고 null guard 안했길래 다 안할 줄 알았는데 요거는 또 되어있넹
	// 근데 tokens 끝에 NULL 안채워주나...?
	// 나중에 순회할 때 배열의 끝임을 어떻게 파악하지
	// 할당 사이즈를 토큰 개수에 하나 더 더한만큼 한 거 보면 분명 NULL을 채우려고 한 것 같은데
	// 나중에 채우나...?
	tokens = make_token(str, tokens);
		// 토큰 만들기~
	return (tokens);
}
