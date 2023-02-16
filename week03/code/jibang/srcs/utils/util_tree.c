#include "../../includes/minishell.h"

t_tree_node	*create_btree_node(t_token *tokens)
{
	t_tree_node	*r_node;

	r_node = (t_tree_node *)ft_calloc(1, sizeof(t_tree_node));
	if (!r_node || !tokens)
		return (NULL);
	r_node->tokens = tokens;
	return (r_node);
}

void	delete_node(t_tree_node *node)
{
	if (node)
	{
		delete_node(node->left);
		delete_node(node->right);
		if (node->tokens)
			delete_token(node->tokens);
		if (node->redir)
			delete_token(node->redir);
		if (node->command)
			delete_token(node->command);
		free(node);
		node = NULL;
	}
}

int	tree_node_type(int type)
{
	if (type == OR)
		return (TN_OR);
	else if (type == AND)
		return (TN_AND);
	else if (type == PIPE)
		return (TN_PIPE);
	else if (type == PARENS)
		return (TN_PARENS);
	else
		return (TN_WORD);
}
