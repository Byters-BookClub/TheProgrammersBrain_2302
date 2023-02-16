#include "../../includes/minishell.h"

static t_token	*check_root_node(t_token *tokens);
static void		cut_btree_node(t_token *token, t_token *root);
static void		set_btree_word(t_tree_node **node);

void	set_btree_node(t_tree_node **node)
{
	t_token	*root;

	if (*node && !((*node)->type))
	{
		root = check_root_node((*node)->tokens);
		if (root)
		{
			(*node)->type = tree_node_type(root->type);
			cut_btree_node((*node)->tokens, root);
			(*node)->left = create_btree_node((*node)->tokens);
			(*node)->tokens = NULL;
			(*node)->right = create_btree_node(root->next);
			free(root->content);
			free(root);
			set_btree_node(&((*node)->left));
			set_btree_node(&((*node)->right));
		}
		else
			set_btree_word(node);
	}
}

static t_token	*check_root_node(t_token *tokens)
{
	t_token	*root_and_or;
	t_token	*root_pipe;

	root_and_or = tokens;
	root_pipe = NULL;
	while (root_and_or)
	{
		if (root_and_or->type == AND || root_and_or->type == OR)
			return (root_and_or);
		if (!root_pipe && root_and_or->type == PIPE)
			root_pipe = root_and_or;
		root_and_or = root_and_or->next;
	}
	return (root_pipe);
}

static void	cut_btree_node(t_token	*token, t_token *root)
{
	if (!token || !root)
		return ;
	while (token->next)
	{
		if (token->next == root)
			break ;
		token = token->next;
	}
	token->next = NULL;
}

static void	set_btree_word(t_tree_node **node)
{
	int		flag;
	t_token	*token;

	flag = 0;
	token = (*node)->tokens;
	(*node)->type = tree_node_type(token->type);
	if ((*node)->type != TN_PARENS)
	{
		while (token)
		{
			if (token->type >= 8 && token->type <= 11)
			{
				flag = 1;
				add_token(&(*node)->redir, new_token(*token));
			}
			else if (flag)
			{
				flag = 0;
				add_token(&(*node)->redir, new_token(*token));
			}
			else
				add_token(&(*node)->command, new_token(*token));
			token = token->next;
		}
	}
}
