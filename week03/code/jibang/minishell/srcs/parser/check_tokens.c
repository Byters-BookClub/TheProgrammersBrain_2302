/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:28:28 by yeblee            #+#    #+#             */
/*   Updated: 2022/11/06 17:23:43 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*check_quote(int *i, char *line)
{
	int		len;
	t_token	buf;
	t_token	*new;

	new = NULL;
	if (line[*i] == '\"')
		buf.type = D_QUOTE;
	else if (line[*i] == '\'')
		buf.type = S_QUOTE;
	len = str_len(line, line[*i], *i + 1, NONE);
	if (!len)
	{
		if (buf.type == S_QUOTE)
			error_exit("minish: syntax error near unexpected token `''");
		else if (buf.type == D_QUOTE)
			error_exit("minish: syntax error near unexpected token `\"'");
		g_var.status = 258;
		return (new);
	}
	buf.content = ft_substr(line, *i, len - *i + 1);
	*i = len + 1;
	new = new_token(buf);
	return (new);
}

t_token	*check_parens(int *i, char *line)
{
	int		len;
	t_token	buf;
	t_token	*new;

	new = NULL;
	buf.type = PARENS;
	len = str_parens(line, *i);
	if (len <= 0)
	{
		if (!len)
			error_exit("minish: syntax error near unexpected token `('");
		else if (len < 0)
			error_exit("minish: syntax error near unexpected token `)'");
		g_var.status = 258;
		return (new);
	}
	buf.content = ft_substr(line, *i, len - *i);
	*i = len;
	new = new_token(buf);
	return (new);
}

t_token	*check_and_or_pipe(int *i, char *line)
{
	int		len;
	t_token	buf;
	t_token	*new;

	len = 2;
	new = NULL;
	if (line[*i + 1] && line[*i] == '|' && line[*i + 1] == '|')
		buf.type = OR;
	else if (line[*i] == '|')
	{
		len = 1;
		buf.type = PIPE;
	}
	else if (line[*i + 1] && line[*i] == '&' && line[*i + 1] == '&')
		buf.type = AND;
	buf.content = ft_substr(line, *i, len);
	*i += len;
	new = new_token(buf);
	return (new);
}

t_token	*check_redir(int *i, char *line)
{
	int		len;
	t_token	buf;
	t_token	*new;

	len = 2;
	new = NULL;
	if (line[*i + 1] && line[*i] == '<' && line[*i + 1] == '<')
		buf.type = HERE_DOC;
	else if (line[*i + 1] && line[*i] == '>' && line[*i + 1] == '>')
		buf.type = APP_RDIR;
	else
	{
		len = 1;
		if (line[*i] == '<')
			buf.type = INP_RDIR;
		else if (line[*i] == '>')
			buf.type = OUT_RDIR;
	}
	buf.content = ft_substr(line, *i, len);
	*i += len;
	new = new_token(buf);
	return (new);
}

t_token	*check_cmd_or_option(int *i, char *line)
{
	int		len;
	t_token	buf;
	t_token	*new;

	new = NULL;
	buf.type = CMD;
	if (line[*i] == '-')
		buf.type = OPTION;
	len = str_len(line, ' ', *i, CMD);
	buf.content = ft_substr(line, *i, len - *i);
	*i = len;
	new = new_token(buf);
	return (new);
}
