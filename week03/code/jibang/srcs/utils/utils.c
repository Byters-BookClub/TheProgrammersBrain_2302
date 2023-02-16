#include "../../includes/minishell.h"

int	str_len(char *str, char c, int i, int type)
{
	while (str[i])
	{
		if (type && ft_strchr("\'\"()|&<>", str[i]))
			return (i);
		if (str[i] == c)
			return (i);
		i++;
	}
	if (!type)
		return (0);
	return (i);
}

int	str_parens(char *str, int i)
{
	int	cnt;

	if (str[i] == ')')
		return (-1);
	i += 1;
	cnt = 1;
	while (cnt && str[i])
	{
		if (str[i] == '(')
			cnt += 1;
		else if (str[i] == ')')
			cnt -= 1;
		i++;
	}
	if (cnt > 0)
		return (0);
	else if (cnt < 0)
		return (-1);
	return (i);
}

void	ft_display_ctrlx_set(int flag)
{
	if (flag == DISPLAY)
		tcsetattr(STDIN_FILENO, TCSANOW, &g_var.display_set);
	else if (flag == NODISPLAY)
		tcsetattr(STDOUT_FILENO, TCSANOW, &g_var.nodisplay_set);
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WCOREFLAG | WTERMSIG(status));
}
