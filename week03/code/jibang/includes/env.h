#ifndef ENV_H
# define ENV_H

t_environ	*get_envp_list(char **env);
t_environ	*get_env_node(char *key);
void		add_env_node(char *key, char *value, t_environ **env_list);
t_environ	*new_env_node(char *key, char *value);
void		lstadd_env_node(t_environ **env_list, t_environ *new);
t_environ	*last_env_node(t_environ *env_list);

#endif
