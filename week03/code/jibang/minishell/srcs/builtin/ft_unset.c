#include "../../includes/minishell.h"

static int	already_exist(char *key);
static void	delete_env_node(t_environ **env_list, char *key);

int	ft_unset(t_token *command)
{
	t_token	*tmp;
	char	*key;

	if (command == NULL || command->next == NULL)
		return (0);
	tmp = command->next;
	while (tmp)
	{
		key = tmp->content;
		if (already_exist(key))
		{
			delete_env_node(&g_var.env_list, key);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	already_exist(char *key)
{
	t_environ	*tmp;
	int			res;

	tmp = g_var.env_list;
	res = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			res = 1;
		tmp = tmp->next;
	}
	return (res);
}

static void	delete_env_node(t_environ **env_list, char *key)
{
	t_environ	*tmp;
	t_environ	*target;

	target = get_env_node(key);
	tmp = *env_list;
	if (env_list == NULL || target == NULL)
		return ;
	while (tmp->next != target)
	{
		tmp = tmp->next;
	}
	target = tmp->next;
	tmp->next = tmp->next->next;
	free(target->key);
	free(target->value);
	free(target);
}
