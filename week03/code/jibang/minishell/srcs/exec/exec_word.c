#include "../../includes/minishell.h"

int	exec_word(t_tree_node *root)
{
	pid_t	pid;
	int		status;
	int		p_status;

	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	p_status = EXIT_SUCCESS;
	if (root->type == TN_PARENS)
		return (exec_parens(root));
	// exit하는 상황이 아닌데 exit_success를 왜 쓴건지 모르겠음..!
	else if (root->command && (check_builtin(root->command) == EXIT_SUCCESS))
		return (run_builtin(root));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			status = exec_word_child(root);
			exit(status);
		}
		waitpid(pid, &p_status, 0);
		return (check_status(p_status));
	}
}

int	exec_last_word_child(t_tree_node *root, t_pipe p)
{
	dup2(p.prev, STDIN_FILENO);
	close(p.prev);
	if (root->type == TN_PARENS)
		exec_parens(root);
	else
	{
		if (check_builtin(root->command) == EXIT_SUCCESS)
			p.status = run_builtin(root);
		else
			p.status = exec_word_child(root);
	}
	return (p.status);
}

// 리다이렉션을 수행하고 명령어를 실행하는구나..
int	exec_word_child(t_tree_node *root)
{
	char	*path;
	char	**env;
	char	**cmd_list;

	if (redirection(root) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (root->command)
	{
		cmd_list = exec_token_str_list(root->command);
		env = exec_env_str_list();
		if (ft_strchr(cmd_list[0], '/'))
			path = cmd_list[0];
		else
			path = exec_find_path(ft_strjoin("/", cmd_list[0]), env);
		if (execve(path, cmd_list, env) == -1)
		{
			ft_perror(*cmd_list, ": command not found");
			return (127);
		}
	}
	return (EXIT_SUCCESS);
}
