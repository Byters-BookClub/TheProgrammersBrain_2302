#include "../../includes/minishell.h"

int	redir_here_doc_check(t_info *info)
{
	int		status;
	t_token	*here_doc;

	status = SUCCESS;
	here_doc = info->h_token;
	g_var.hd_cnt = 0;
	while (here_doc)
	{
		if (here_doc->type == AND || here_doc->type == OR \
			|| here_doc->type == PIPE)
			g_var.hd_cnt++;
		if (here_doc->type == HERE_DOC)
		{
			here_doc->hd_num = g_var.hd_cnt;
			status = redir_here_doc_file(here_doc);
		}
		here_doc = here_doc->next;
	}
	if (!status)
		g_var.status = EXIT_FAILURE;
	return (status);
}

void	redir_unlink(void)
{
	int		hd_cnt;
	char	*filename;

	hd_cnt = 0;
	while (hd_cnt <= g_var.hd_cnt)
	{
		filename = ft_strjoin(".here_doc", ft_itoa(hd_cnt));
		if (access(filename, F_OK) == 0)
			unlink(filename);
		free(filename);
		hd_cnt++;
	}
}
