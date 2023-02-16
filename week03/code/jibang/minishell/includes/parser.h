#ifndef PARSER_H
# define PARSER_H

/* check_tokens.c */
t_token	*check_quote(int *i, char *line);
t_token	*check_parens(int *i, char *line);
t_token	*check_and_or_pipe(int *i, char *line);
t_token	*check_redir(int *i, char *line);
t_token	*check_cmd_or_option(int *i, char *line);

/* set_btree.c */
void	set_btree_node(t_tree_node **node);

/* tokenizer.c */
void	tokenizer(t_token **tokens, char *cmd_line);

#endif