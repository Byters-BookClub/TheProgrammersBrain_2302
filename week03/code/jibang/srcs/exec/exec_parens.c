#include "../../includes/minishell.h"

int	exec_parens(t_tree_node *root)
{
	pid_t	pid;
	int		status;
	char	*cmd_line;

	status = EXIT_SUCCESS;
	cmd_line = exec_rm_char(root->tokens);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		if (cmd_line)
			exec_set(cmd_line);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	return (check_status(status));
}
