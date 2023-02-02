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
	char	*new_ret;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_ret = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_ret)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		new_ret[i] = s1[i];
	j = -1;
	while (++j < s2_len)
		new_ret[i + j] = s2[j];
	free(s1);
	ft_memmove(s2, s2_len);
	return (new_ret);
}

int	ft_strchr(char *s)
{
	while (*s && *s != '\n')
		s++;
	if (*s == '\n')
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*ret;
	int			read_value;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = malloc(sizeof(char));
	if (!ret)
		return (NULL);
	*ret = 0;
	while (ft_strchr(ret))
	{
		if (!buffer[0])
		{
			read_value = read(fd, buffer, BUFFER_SIZE);
			if (!read_value && ret[0] != 0)
				return (ret);
			else if (read_value < 0 || (!read_value && !ret[0])) 
			{
				free(ret);
				return (NULL);
			}
		}
		ret = ft_strjoin(ret, buffer);
		if (!ret)
			return (NULL);
	}
	return (ret);
}