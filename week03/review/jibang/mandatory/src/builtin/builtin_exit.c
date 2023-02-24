/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:24:02 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/23 22:50:07 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"

static int	pass_sign_and_zeros(char *argument, int *i)
{
	int	idx;
	int	sign;

	idx = 0;
	sign = 1;
	if (argument[idx] == '+' || argument[idx] == '-')
	{
		if (argument[idx] == '-')
			sign = -1;
		idx++;
	}
	while (argument[idx] == '0')
		idx++;
	*i += idx;
	return (sign);
}

static int	is_numeric_argument(char *argument, int *exit_stat)
{
	int	i;
	int	len;
	int	sign;

	i = 0;
	len = 0;
	sign = pass_sign_and_zeros(argument, &i);
	while (argument[i] && len < 19)
	{
		if (!ft_isdigit(argument[i]))
			return (0);
		*exit_stat = (*exit_stat * 10 + (int)(argument[i] - '0')) & 255;
		i++;
		len++;
	}
	if (len == 19 && (argument[i] || (sign == 1 && argument[i - 1] >= '8') \
									|| (sign == -1 && argument[i - 1] >= '9')))
		return (0);
	return (1);
}

static void	exit_terminate_with_no_error(int exit_stat, int is_arg)
{
	if (is_arg)
	{
		if (exit_stat < 0)
			exit_stat = (exit_stat) & 255 + 256;
		exit_stat_update(exit_stat);
	}
	exit_program();
}

static void	exit_terminate_with_error(char *arg, int errcode)
{
	handle_builtin_error(errcode, CMD_EXIT, arg);
	if (errcode == ERR_B_NOT_NUMBER)
		exit_program();
}

void	builtin_exit(char *argv[])
{
	int	exit_stat;

	printf("exit\n"); // 셸을 까먹어서 잘 기억이 안나는데.. argv를 체크할 일이 있었는지 가물가물하다. 다만 케이스별로 어떤 함수를 호출하겠다는 것은 의미가 잘 전달이 된다.
	if (!argv)
		exit_program();
	if (argv[1])
	{
		exit_stat = 0;
		if (!is_numeric_argument(argv[1], &exit_stat))
			exit_terminate_with_error(argv[1], ERR_B_NOT_NUMBER);
		if (argv[2])
			exit_terminate_with_error(NULL, ERR_B_TOO_MANY_ARGUMENTS);
		else
			exit_terminate_with_no_error(exit_stat, 1);
	}
	else
		exit_terminate_with_no_error(0, 0);
}
