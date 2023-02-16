#include "../../includes/minishell.h"

int	exec_and_or(t_info *info, t_tree_node *root)
{
	if (root->left->type == TN_WORD)
		g_var.status = exec_word(root->left);
	if (root->left->type == TN_PARENS)
		g_var.status = exec_parens(root->left);
	if (root->left->type == TN_PIPE)
		g_var.status = exec_pipe(root->left);
	if ((root->type == TN_AND && g_var.status == EXIT_SUCCESS) || \
		(root->type == TN_OR && g_var.status != EXIT_SUCCESS))
		execute_btree_node(info, root->right);
	return (g_var.status);
}
