#include "../../includes/minishell.h"

int	ft_pwd(t_token *command)
{
	char	*path;

	if (command == NULL)
		return (0);
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putstr_fd("path not found\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(path);
	return (0);
}
