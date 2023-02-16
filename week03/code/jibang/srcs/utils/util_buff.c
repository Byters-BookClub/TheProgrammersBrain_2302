#include "../../includes/minishell.h"

void	add_str_buff(char **buff, char *str)
{
	*buff = ft_strjoin(*buff, str);
}

void	add_char_buff(char **buff, char c)
{
	char	*ch;

	ch = malloc(sizeof(char) + 1);
	if (!ch)
		return ;
	ch[0] = c;
	ch[1] = '\0';
	*buff = ft_strjoin(*buff, ch);
	free(ch);
}
