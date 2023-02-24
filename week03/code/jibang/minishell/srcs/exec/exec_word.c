#include "../../includes/minishell.h"

int	exec_word(t_tree_node *root)
{
	pid_t	pid;
	int		status;
	int		p_status;

	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	p_status = EXIT_SUCCESS;
	// exec_word를 호출하는 함수의 type이 word인데 이 함수 내부에서 서브쉘인지 다시 한번 확인한다.
	// 아마 서브쉘 로직에서 이 함수를 호출하기 때문인 것 같은데.. 만약 로직이 수정가능하다면 
	// 두 함수를 완전히 분리하는 것이 좋을 것 같다
	if (root->type == TN_PARENS)
		return (exec_parens(root));
	// exit하는 상황이 아닌데 exit_success를 사용한 점이 다소 아쉽다.
	else if (root->command && (check_builtin(root->command) == EXIT_SUCCESS))
		return (run_builtin(root));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			// exec_word_child에서 exit을 호출하지 않고, 해당 함수 윗단계에서 exit분기를 건 명시하는 건 좋은 것 같다
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
