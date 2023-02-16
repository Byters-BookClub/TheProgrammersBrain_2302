#ifndef EXEC_H
# define EXEC_H

/* execution */
int		exec_set(char *cmd_line);
int		execution(t_info *info);
int		execute_btree_node(t_info *info, t_tree_node *root);

/* exec_parens */
int		exec_parens(t_tree_node *root);

/* exec_and_or */
int		exec_and_or(t_info *info, t_tree_node *root);

/* exec_pipe */
int		exec_pipe(t_tree_node *root);

/* exec_word */
int		exec_word(t_tree_node *root);
int		exec_word_child(t_tree_node *root);
int		exec_last_word_child(t_tree_node *root, t_pipe p);

#endif