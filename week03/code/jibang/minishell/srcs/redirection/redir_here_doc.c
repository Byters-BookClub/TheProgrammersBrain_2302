#include "../../includes/minishell.h"

static void	redir_here_doc_child(char *limiter);

int	redir_here_doc_file(t_token *token)
{
	pid_t	pid;
	char	*limiter;

	limiter = exec_rm_char(token->next);
	if (!limiter)
		return (FALSE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, sig_here_doc);
		redir_here_doc_child(limiter);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &pid, 0);
		if (check_status(pid) == 130)
			return (FALSE);
	}
	return (SUCCESS);
}

static void	redir_here_doc_child(char *limiter)
{
	int		hd_fd;
	char	*line;
	char	*hd_filename;

	signal(SIGINT, SIG_DFL);
	hd_filename = ft_strjoin(".here_doc", ft_itoa(g_var.hd_cnt));
	hd_fd = open(hd_filename, O_CREAT | O_RDWR | O_TRUNC, 0744);
	if (hd_fd == -1)
	{
		ft_perror(hd_filename, ": No such file or directory");
		exit(EXIT_FAILURE);
	}
	line = readline("> ");
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		if (ft_strchr(line, '$'))
			line = check_expand(line);
		ft_putstr_fd(line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(line);
		line = readline("> ");
	}
	close(hd_fd);
	exit(EXIT_SUCCESS);
}
