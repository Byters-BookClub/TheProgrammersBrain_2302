#include "../../includes/minishell.h"

int	ft_exit(t_token *command)
{
	int		code;

	if (command == NULL)
		return (0);
	if (command->next == NULL)
	{
		exit(0);
	}
	code = ft_atoi(command->next->content);
	exit(code);
}
