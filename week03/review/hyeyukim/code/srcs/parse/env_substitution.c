/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:37 by jonkim            #+#    #+#             */
/*   Updated: 2023/02/24 05:20:37 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

// 뭐 하는 함수인지 이름으로 파악할 수가 없다.

char	*ret_sub(char *str, char *sub, int pos1, int pos2)
{
	char	*ret;
	int		i;
	int		j;
	int		idx;

	i = -1;
	j = 0;
	idx = 0;
	ret = ft_calloc(ft_strlen(str) - pos2 + pos1 + ft_strlen(sub) + 1, 1);
	if (!sub)
		sub = ft_strdup("");
	sub = ft_strdup(sub);
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (i < pos2 && i >= pos1)
			while (sub[j])
				ret[idx++] = sub[j++];
		else
			ret[idx++] = str[i];
	}
	free(sub);
	free(str);
	return (ret);
}

// 무엇을 substitute하는지 그 대상을 표현하면 좋을 것 같고 함수명은 동사로 작성하는게 좋을 것 같다.
// 또한 expand가 보다 더 적합한 용어라고 생각된다.
// substitution -> expand_variable
// 또 매개변수가 무엇을 의미하는지 파악하기 너무 어렵다.
// s는 그렇다치고 대체 p1과 p2가 의미하는 건 무엇인지 알 수가 없다.
// pointer의 줄임말인가 싶었는데 p2의 경우에는 pointer도 아니었다.
// 그렇다면 point인가 싶었는데 맥락상 맞지 않다.
// char *substitution -> char *expand_variable(char *str, int *offset, int len, int idx)
char	*substitution(char *s, int *p1, int p2, int i)
{
	int		j;
	char	*key;
	char	*sub;

	while (s[++i]) 
		// 증감 연산자를 while문 조건문에 작성하기 위해 이 함수를 호출할때 네 번째 인자로 
		// i-1값을 넣는데 상당히 혼란스럽다.
	{
		j = i + 1; // j는 무엇을 위한거지... 아 항상 i 뒤의 값을 확인하겠다는 거구만
					// 굳이 변수를 따로 정의할 필요가 있나...?
		if (s[i] == '$' && j <= p2)
		{
			// $? expansion
			if (s[j] == '?')
				return (ret_sub(s, get_env_value("?"), i, j + 1));
				// ret_sub가 무슨 함수일까. 설마 result_of_substitution의 줄임말인가.
			if (s[j] && s[j] != '_' && !a(s[j]) && s[j] != '$' && s[j] != ' ')
				if ((s[j] != '\'' && s[j] != '\"') || !find_c(s + j + 1, s[j]))
					return (ret_sub(s, NULL, i, j + 1));
				// 이중 if문을 사용한 이유가 뭐지... 혼란스럽다...
				// 그리고 함수 이름이 a...? 대체 뭐하는 함수지? 내부에서 ft_isalpha를 반환하고 있네..
				// 그냥 조건문을 따로 함수로 빼는게 차라리 나을 것 같다.
				// ret_sub에 NULL을 넣으면 무슨 일이 일어나는거지... 그냥 s반환?, NULL반환?
			while (j <= p2 && s[j] && (ft_isalnum(s[j]) || s[j] == '_')) // 변수가 숫자로 시작할 수 있는건가?
				j++;
			key = ft_substr(s, i + 1, j - i - 1); // key 찾기
			sub = get_env_value(key); // expansion 결과값 찾기
			*p1 += ft_strlen(sub) - 1; // pointer 밀어주기
			free(key); // key는 free 해주기
			return (ret_sub(s, sub, i, j));
		}
	}
	return (s);
}

// 어순은 check_env가 보다 더 자연스러울 것 같다.
// 또한 정확하게 무엇을 확인하는 함수인지 이름에서 명시되면 좋을 것 같다.
// env_check -> expand_word
char	*env_check(char *str)
{
	int		i;
	int		tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = i + 1;
			while (str[tmp] && str[tmp] != str[i])
				tmp++;
			if (str[tmp] == '\'')
			{
				str = quote_trim(str, i, tmp);
				i = tmp - 2;
			}
			else if (str[tmp] == '\"')
				str = double_quote_trim(str, &i, tmp);
		}
		else if (str[i] == '$')
			str = substitution(str, &i, ft_strlen(str), i - 1); // i - 1을 넣는 이유는 뭐지, 차라리 i + 1은 납득하겠는데...
				// substitution -> expand_variable
				// while문 돌면서 계속해서 ft_strlen을 호출하는건가
				// 이런건 const 변수 하나 선언해서 값을 구해놓는게 좋을 것으로 보임
	}
	return (str);
}

// 파싱 단계에서 expansion을 하는 것으로 보인다.
// 개인적으로 함수는 동사로 표현하는게 좋은 것 같다.
// env_sub 대신 substitute_env는 어떨까
// 사실 substitute보다는 expand가 더 맞는 표현인 것 같긴 하다.
// 먼저, variable expansion뿐만 아니라 quote removal도 함께 하고 있기 때문이다.
// POSIX에서는 이를 word_expansion이라는 용어로 설명하고 있다.
// 또한, POSIX shell에서 expansion 중에서도 command substitution을 표현할 때
// substitution이라는 단어를 사용하기 때문에 보다 포괄적인 의미를 담은 expand가 적절하다고 생각한다.
// (추천) env_sub -> expand_words, expand_word_list
int	env_sub(t_token_list *list)
{
	t_token_list	*cur;

	cur = list;
	while (cur)
	{
		if (cur->token.type == WORD && cur->token.str)
			cur->token.str = env_check(cur->token.str);
				// 확인 대상이 명시되어 있지 않아서 정확하게는 모르겠으나
				// 아마도 token 문자열에 $변수가 있는지 확인하고 있으면 바꿔주는 것 같음 
		cur = cur->next;
	}
	return (0);
}
