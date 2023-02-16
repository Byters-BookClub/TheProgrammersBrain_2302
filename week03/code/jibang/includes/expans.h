#ifndef EXPANS_H
# define EXPANS_H

/* wildcard.c */
void	aster_replace(t_token **tokens_list);

/* wildcard_utils.c */
int		is_aster_token(t_token token);
char	*get_prefix(char *str);
char	*get_suffix(char *str);
void	token_replace(t_token **tokens_list, t_token *target, \
						t_token *expan_tokens);
t_token	*ft_tokenlast(t_token *lst);

/* wildcard_caseby.c */
int		case_zero(char *d_name, t_token *token, t_token **expan_token);
int		case_one(char *d_name, char *prefix, t_token *token, \
					t_token **expan_token);
int		case_two(char *d_name, char *suffix, t_token *token, \
					t_token **expan_token);
int		case_three(char *d_name, t_aster *ast, t_token *token, \
					t_token **expan_token);

#endif
