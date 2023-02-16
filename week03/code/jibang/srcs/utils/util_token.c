#include "../../includes/minishell.h"

t_token	*new_token(t_token token)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = token.type;
	new->content = token.content;
	if (token.hd_num)
		new->hd_num = token.hd_num;
	return (new);
}

void	add_token(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (!token_list)
		return ;
	if (!new)
	{
		*token_list = NULL;
		token_list = NULL;
		return ;
	}
	if (!*token_list)
	{
		*token_list = new;
		return ;
	}
	last = get_last_token(*token_list);
	last->next = new;
}

t_token	*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (!tokens->next)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

int	get_token_length(t_token *tokens)
{
	int		len;
	t_token	*tmp;

	len = 0;
	tmp = tokens;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	*delete_token(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens);
		tokens = next;
	}
	return (NULL);
}
