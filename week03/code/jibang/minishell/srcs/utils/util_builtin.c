#include "../../includes/minishell.h"

int	check_builtin(t_token *token)
{
	char	*cmd;

	if (!token)
		return (EXIT_FAILURE);
	cmd = token->content;
	if (!ft_strcmpi(cmd, "echo") || \
		!ft_strcmpi(cmd, "cd") || \
		!ft_strcmpi(cmd, "pwd") || \
		!ft_strcmpi(cmd, "export") || \
		!ft_strcmpi(cmd, "unset") || \
		!ft_strcmpi(cmd, "env") || \
		!ft_strcmpi(cmd, "exit"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	run_builtin(t_tree_node *root)
{
	char	*cmd;

	if (redirection(root) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (root && root->command && root->command->content)
	{
		cmd = root->command->content;
		if (!ft_strcmpi(cmd, "echo"))
			return (ft_echo(root->command));
		if (!ft_strcmpi(cmd, "cd"))
			return (ft_cd(root->command));
		if (!ft_strcmpi(cmd, "pwd"))
			return (ft_pwd(root->command));
		if (!ft_strcmpi(cmd, "export"))
			return (ft_export(root->command));
		if (!ft_strcmpi(cmd, "unset"))
			return (ft_unset(root->command));
		if (!ft_strcmpi(cmd, "env"))
			return (ft_env(root->command));
		if (!ft_strcmpi(cmd, "exit"))
			return (ft_exit(root->command));
	}
	return (EXIT_FAILURE);
}
