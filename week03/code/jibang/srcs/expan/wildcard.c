#include "../../includes/minishell.h"

static void	get_expans_list(t_token *token, t_token **expan_token);

void	aster_replace(t_token **tokens_list)
{
	t_token	*tmp;
	t_token	*expan_tokens;

	tmp = *tokens_list;
	expan_tokens = NULL;
	while (tmp)
	{
		if (is_aster_token(*tmp))
		{
			get_expans_list(tmp, &expan_tokens);
			token_replace(tokens_list, tmp, expan_tokens);
		}
		tmp = tmp->next;
	}
}

static void	get_expans_list(t_token *token, t_token **expan_token)
{
	struct dirent	*dirent;
	DIR				*dir;
	t_aster			*ast;

	ast = malloc(sizeof(t_aster));
	ast->prefix = get_prefix(token->content);
	ast->suffix = get_suffix(token->content);
	dir = opendir(".");
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (!ast->prefix && !ast->suffix)
			case_zero(dirent->d_name, token, expan_token);
		else if (ast->prefix && !ast->suffix)
			case_one(dirent->d_name, ast->prefix, token, expan_token);
		else if (!ast->prefix && ast->suffix)
			case_two(dirent->d_name, ast->suffix, token, expan_token);
		else if (ast->prefix && ast->suffix)
			case_three(dirent->d_name, ast, token, expan_token);
	}
	closedir(dir);
}
