#ifndef REDIRECTION_H
# define REDIRECTION_H

int		redirection(t_tree_node *root);
int		redir_open_file(char *filename, int type);
int		redir_here_doc_file(t_token *token);
void	redir_unlink(void);
#endif
