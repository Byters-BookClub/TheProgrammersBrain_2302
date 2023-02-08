/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:16:05 by jibang            #+#    #+#             */
/*   Updated: 2022/03/20 20:57:18 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	how_many_words(char const *s, char c)
{
	size_t	x;
	size_t	word_cnt;

	x = 0;
	word_cnt = 0;
	while (s[x])
	{
		while (s[x] && s[x] == c)
			x++;
		while (s[x] && s[x] != c)
		{
			x++;
			if (s[x] == c || s[x] == '\0')
				word_cnt++;
		}
	}
	return (word_cnt);
}

static size_t	*word_len(char const *s, char c, size_t word_cnt)
{
	size_t	x;
	size_t	*lens;
	size_t	len;
	size_t	i;

	i = 0;
	x = 0;
	lens = (size_t *) malloc(sizeof(size_t) * word_cnt);
	if (!lens)
		return (NULL);
	while (s[x])
	{
		len = 0;
		while (s[x] && s[x] == c)
			x++;
		while (s[x] && s[x] != c)
		{
			x++;
			len++;
			if (s[x] == c || s[x] == '\0')
				lens[i++] = len;
		}
	}
	return (lens);
}

char	**cpy_each_word(char **pstr, char const *s, char c)
{
	size_t	i;
	size_t	x;
	size_t	*lens;
	size_t	word_cnt;

	i = 0;
	x = 0;
	word_cnt = how_many_words(s, c);
	lens = word_len(s, c, word_cnt);
	while (s[x] && s[x] == c)
		x++;
	while (s[x])
	{
		if (s[x] != c && i < word_cnt)
		{
			ft_strlcpy(pstr[i], s + x, lens[i] + 1);
			x = x + lens[i] - 1;
			i++;
		}
		x++;
	}
	free(lens);
	pstr[word_cnt] = NULL;
	return (pstr);
}

char	**free_all_and_null(char **pstr, size_t i, size_t *lens)
{
	if (i != 0)
	{
		i--;
		while (i)
		{
			free(pstr[i]);
			i--;
		}
		if (i == 0)
			free(pstr[i]);
	}
	free(pstr);
	free(lens);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_cnt;
	char	**pstr;
	size_t	*lens;
	size_t	i;

	if (s == NULL)
		return (NULL);
	word_cnt = how_many_words(s, c);
	pstr = (char **) malloc(sizeof(char *) * (word_cnt + 1));
	if (!pstr)
		return (NULL);
	lens = word_len(s, c, word_cnt);
	i = 0;
	while (i < word_cnt)
	{
		pstr[i] = (char *) malloc(sizeof(char) * (lens[i] + 1));
		if (!pstr[i])
			return (free_all_and_null(pstr, i, lens));
		i++;
	}
	pstr = cpy_each_word(pstr, s, c);
	free(lens);
	return (pstr);
}
