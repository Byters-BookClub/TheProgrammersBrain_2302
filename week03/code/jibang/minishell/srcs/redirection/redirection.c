#include "../../includes/minishell.h"

static int	redir_open_fd(t_token *token);

int	redirection(t_tree_node *root)
{
	t_token	*token;
	int		r_status;

	r_status = EXIT_SUCCESS;
	token = root->redir;
	while (token)
	{
		if (token->type >= INP_RDIR && token->type <= HERE_DOC)
			r_status = redir_open_fd(token);
		if (r_status != EXIT_SUCCESS)
			break ;
		token = token->next->next;
	}
	return (r_status);
}

static int	redir_open_fd(t_token *token)
{
	int		r_status;
	char	*filename;

	filename = NULL;
	if (!token->next)
		return (EXIT_FAILURE);
	if (token->type == HERE_DOC)
		filename = ft_strjoin(".here_doc", ft_itoa(token->hd_num));
	else
		filename = token->next->content;
	if (!filename)
		return (EXIT_FAILURE);
	r_status = redir_open_file(filename, token->type);
	if (r_status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (r_status);
}

int	redir_open_file(char *filename, int type)
{
	int	fd;

	fd = -1;
	if ((type == INP_RDIR || type == HERE_DOC) && (access(filename, F_OK) == 0))
	{
		fd = open(filename, O_RDONLY | O_CLOEXEC, 0777);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		if (type == OUT_RDIR)
			fd = open(filename, O_TRUNC | O_CREAT | O_RDWR, 0644);
		else if (type == APP_RDIR)
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
	{
		ft_perror(filename, ": No such file or directory");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
