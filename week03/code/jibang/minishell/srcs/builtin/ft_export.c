#include "../../includes/minishell.h"

static void	show_env_list(t_environ *env_list);
static int	already_exist(char *key);
static void	update_env_var(char *key, char *val);
static void	do_export(t_token *tmp, int i, int flag);

int	ft_export(t_token *command)
{
	t_token	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (command == NULL)
		return (0);
	if (command->next == NULL)
		show_env_list(g_var.env_list);
	tmp = command->next;
	while (tmp)
	{
		do_export(tmp, i, flag);
		tmp = tmp->next;
	}
	return (0);
}

static void	do_export(t_token *tmp, int i, int flag)
{
	char	*key;
	char	*val;

	while (tmp->content[i] && tmp->content[i] != '=')
	{
		i++;
		if (tmp->content[i] == '=')
			flag = 1;
	}
	key = malloc(sizeof(char) * (i + 1));
	val = NULL;
	ft_strlcpy(key, tmp->content, i + 1);
	if (flag)
	{
		val = malloc(sizeof(char) * (ft_strlen(tmp->content) + 1));
		ft_strlcpy(val, (tmp->content + i + 1), (ft_strlen(tmp->content) - i));
	}
	if (already_exist(key))
		update_env_var(key, val);
	else
		add_env_node(key, val, &g_var.env_list);
}

static void	show_env_list(t_environ *env_list)
{
	t_environ	*tmp;

	tmp = env_list;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
}

static int	already_exist(char *key)
{
	t_environ	*tmp;
	int			res;

	tmp = g_var.env_list;
	res = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)) == 0)
			res = 1;
		tmp = tmp->next;
	}
	return (res);
}

static void	update_env_var(char *key, char *val)
{
	t_environ	*tmp;

	tmp = g_var.env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)) == 0)
		{
			free(tmp->value);
			tmp->value = val;
		}
		tmp = tmp->next;
	}
}
