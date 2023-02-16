#include "../../includes/minishell.h"

static void	show_env_list(t_environ *env_list);

int	ft_env(t_token *command)
{
	if (command == NULL)
		return (0);
	show_env_list(g_var.env_list);
	return (0);
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
