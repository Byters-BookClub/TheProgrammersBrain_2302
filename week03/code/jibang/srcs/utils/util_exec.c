#include "../../includes/minishell.h"

void	exec_make_env_str(char **env)
{
	int			i;
	char		*tmp;
	char		*str_env;
	t_environ	*env_list;

	i = 0;
	env_list = g_var.env_list;
	while (env_list)
	{
		if (env_list->value)
		{
			tmp = ft_strjoin(env_list->key, (char *)"=");
			str_env = ft_strjoin(tmp, env_list->value);
			free(tmp);
			env[i++] = str_env;
		}
		env_list = env_list->next;
	}
	env[i] = NULL;
}

char	**exec_env_str_list(void)
{
	int			i;
	t_environ	*env_list;
	char		**env;

	i = 0;
	env_list = g_var.env_list;
	while (env_list)
	{
		if (env_list->value)
			i++;
		env_list = env_list->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		exit(EXIT_FAILURE);
	exec_make_env_str(env);
	return (env);
}

char	**exec_token_str_list(t_token *token)
{
	int		i;
	int		len;
	t_token	*tmp;
	char	**cmd_list;

	i = 0;
	if (!token)
		return (NULL);
	len = get_token_length(token) + 1;
	cmd_list = NULL;
	cmd_list = malloc(sizeof(char *) * (len + 1));
	if (!cmd_list)
		exit(EXIT_FAILURE);
	tmp = token;
	while (tmp)
	{
		cmd_list[i++] = exec_rm_char(tmp);
		tmp = tmp->next;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}

char	*exec_find_path(char *cmd, char *envp[])
{
	int			i;
	char		*path;
	char		**paths;
	t_environ	*env_path;

	i = 0;
	env_path = get_env_node("PATH");
	if (!env_path || (env_path && !env_path->value))
		return (NULL);
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*exec_rm_char(t_token *token)
{
	char	*result;
	char	*content;

	if (!token)
		return (NULL);
	if (!token->content)
		return (NULL);
	content = token->content;
	if (content[0] != '\'' && \
		content[0] != '\"' && \
		content[0] != '(' )
		return (content);
	result = malloc(sizeof(char) * (ft_strlen(content) + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, content + 1, ft_strlen(content) - 1);
	return (result);
}
