/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 18:34:43 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "heredoc.h"
#include "msgdef.h"
#include "executor_internal.h"

int	process_redir(t_redir *redir_arr, int n_redir)
{
	const t_do_redir	do_redir[5] = {
	[REDIR_NONE] = 0, [REDIR_IN] = do_redir_in, [REDIR_OUT] = do_redir_out,
	[REDIR_IN_HERE] = do_redir_in_here, [REDIR_OUT_APPEND] = do_redir_out_append
	};
	int					i;

	i = -1;
	while (++i < n_redir)
	{
		if (redir_arr[i].type == REDIR_NONE)
		{
			ft_dprintf(2, "critical error: redir type is none\n");
			continue ;
		}
		if (do_redir[redir_arr[i].type](redir_arr + i) != CODE_OK)
			return (CODE_ERROR_IO);
	}
	return (CODE_OK);
}

int	do_redir_in(t_redir *redir_arr)
{
	int	fd;

	if (access(redir_arr->content, F_OK) != 0)
	{
		ft_dprintf(2, "%s%s: No such file or directory\n",
			MSG_ERROR_PREFIX, redir_arr->content);
		return (CODE_ERROR_IO);
	}
	if (access(redir_arr->content, R_OK) != 0)
	{
		ft_dprintf(2, "%s%s: Permission denied\n",
			MSG_ERROR_PREFIX, redir_arr->content);
		return (CODE_ERROR_IO);
	}
	fd = open(redir_arr->content, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	do_redir_out(t_redir *redir_arr)
{
	int	fd;

	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	do_redir_in_here(t_redir *redir_arr)
{
	int		fd;
	char	*heredoc_file;

	(void)redir_arr;
	if (heredoc_get_next_filename(&heredoc_file) != CODE_OK)
		return (CODE_ERROR_IO);
	fd = open(heredoc_file, O_RDONLY);
	free(heredoc_file);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	do_redir_out_append(t_redir *redir_arr)
{
	int	fd;

	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}
