#include "../../includes/minishell.h"

static int	check_valid_token(t_token *token);
static int	check_valid_next_token(int prev_type, int cur_type);

void	error_exit(char *str)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	ft_perror(char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(err_msg1, STDERR_FILENO);
	ft_putendl_fd(err_msg2, STDERR_FILENO);
}

int	check_syntax_error(t_token *token)
{
	if (!token)
		return (FALSE);
	if (token->type == AND || token->type == OR || token->type == PIPE)
	{
		ft_perror("syntax error near unexpected token `", \
		ft_strjoin(token->content, "\'"));
		return (FALSE);
	}
	return (check_valid_token(token));
}

static int	check_valid_token(t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	char	*errmsg;

	errmsg = "syntax error near unexpected token `";
	tmp = token;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
		if (check_valid_next_token(prev->type, tmp->type) == FALSE)
		{
			if (prev->type >= INP_RDIR && prev->type <= HERE_DOC)
				ft_perror(errmsg, ft_strjoin(tmp->content, "\'"));
			else
				ft_perror(errmsg, ft_strjoin(prev->content, "\'"));
			return (FALSE);
		}
	}
	if (!(tmp->type >= CMD && tmp->type <= S_QUOTE) && tmp->type != PARENS)
	{
		ft_perror(errmsg, ft_strjoin(tmp->content, "\'"));
		return (FALSE);
	}
	return (SUCCESS);
}

static int	check_valid_next_token(int prev_type, int cur_type)
{
	if ((prev_type == CMD && cur_type == PARENS) || \
		(prev_type == PARENS && cur_type == CMD) || \
		(prev_type == PARENS && cur_type == PARENS))
		return (FALSE);
	if ((prev_type >= INP_RDIR && prev_type <= HERE_DOC) && \
		!(cur_type >= CMD && cur_type <= S_QUOTE))
		return (FALSE);
	if ((prev_type >= OR && prev_type <= PIPE) && \
		(cur_type >= OR && cur_type <= PIPE))
		return (FALSE);
	return (SUCCESS);
}
