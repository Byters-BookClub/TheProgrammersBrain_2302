#include "../../includes/minishell.h"

static void	expand_replace(char **buff, char *str, int *idx);
static char	*get_str_env(char *str, int *idx);
static	int	expand_key_end(char *str);

void	expand(t_token **h_token)
{
	t_token	*token;

	token = *h_token;
	while (token)
	{
		if (token->type >= CMD && token->type <= D_QUOTE)
			token->content = check_expand(token->content);
		token = token->next;
	}
}

char	*check_expand(char *str)
{
	int		i;
	char	*buff;

	i = 0;
	buff = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			expand_replace(&buff, &str[i], &i);
		else
			add_char_buff(&buff, str[i]);
		i++;
	}
	return (buff);
}

static void	expand_replace(char **buff, char *str, int *idx)
{
	char	*value;

	if (str[1] && str[1] == '?')
	{
		*idx += 1;
		add_str_buff(buff, ft_itoa(g_var.status));
		return ;
	}
	if ((str[1] && str[1] == '$') || !str[1])
	{
		add_char_buff(buff, '$');
		return ;
	}
	value = get_str_env(str, idx);
	if (value)
		add_str_buff(buff, value);
}

static char	*get_str_env(char *str, int *idx)
{
	int			end;
	char		*env_key;
	t_environ	*env_node;

	end = expand_key_end(&str[1]);
	*idx += end;
	env_key = ft_substr(str, 1, end);
	env_node = get_env_node(env_key);
	if (!env_node)
		return (ft_strdup(""));
	return (ft_strdup(env_node->value));
}

static int	expand_key_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}
