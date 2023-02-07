#include "get_next_line.h"

int	ft_strlen(char	*s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

void	ft_memmove(char	*s, int len)
{
	int	j;
	int	i;

	i = -1;
	j = len;
	while (++i < BUFFER_SIZE - len)
		s[i] = s[j++];
	while (i < BUFFER_SIZE)
		s[i++] = 0;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*joined;
	const int	s1_len = ft_strlen(s1);
	const int	s2_len = ft_strlen(s2);
	int			i;

	joined = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		joined[s1_len + i] = s2[i];
		i++;
	}
	free(s1);
	ft_memmove(s2, s2_len);
	return (joined);
}

// 원본 함수 형태 그대로 사용하기.
char	*ft_strchr(char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (s);
	return (NULL);
}
