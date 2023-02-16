#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_environ
{
	char				*key;
	char				*value;
	struct s_environ	*next;
}	t_environ;

typedef struct s_global
{
	int				status;
	int				hd_cnt;
	t_environ		*env_list;
	char			*prev_path;
	int				old_std_fdin;
	int				old_std_fdout;
	struct termios	nodisplay_set;
	struct termios	display_set;
}	t_global;

typedef struct s_token
{
	enum e_token_type	type;
	int					hd_num;
	char				*content;
	struct s_token		*next;
}	t_token;

typedef struct s_tree_node
{
	enum e_node_type	type;
	t_token				*tokens;
	t_token				*command;
	t_token				*redir;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_info
{
	t_tree_node	*r_node;
	t_token		*h_token;
}	t_info;

typedef struct s_pipe
{
	pid_t	pid;
	int		cnt;
	int		fd[2];
	int		prev;
	int		status;
}	t_pipe;

typedef struct s_aster
{
	char	*prefix;
	char	*suffix;
}	t_aster;

#endif
