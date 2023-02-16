#include "../../includes/minishell.h"

int	exec_set(char *cmd_line)
{
	int		status;
	t_info	info;

	status = EXIT_SUCCESS;
	info.h_token = NULL;
	tokenizer(&(info.h_token), cmd_line);
	expand(&(info.h_token));
	aster_replace(&(info.h_token));
	if (check_syntax_error(info.h_token) == SUCCESS && \
		redir_here_doc_check(&info) == SUCCESS)
	{
		info.r_node = create_btree_node(info.h_token);
		set_btree_node(&(info.r_node));
		ft_display_ctrlx_set(DISPLAY);
		status = execution(&info);
		ft_display_ctrlx_set(NODISPLAY);
		free(cmd_line);
	}
	else
		delete_token(info.h_token);
	redir_unlink();
	return (status);
}

int	execution(t_info *info)
{
	int	status;

	status = EXIT_SUCCESS;
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	status = execute_btree_node(info, info->r_node);
	delete_node(info->r_node);
	return (status);
}

int	execute_btree_node(t_info *info, t_tree_node *root)
{
	if (!root)
		return (EXIT_FAILURE);
	if (root->type == TN_WORD)
		g_var.status = exec_word(root);
	else if (root->type == TN_PARENS)
		g_var.status = exec_parens(root);
	else if (root->type == TN_AND || root->type == TN_OR)
		exec_and_or(info, root);
	else if (root->type == TN_PIPE)
		g_var.status = exec_pipe(root);
	return (g_var.status);
}
