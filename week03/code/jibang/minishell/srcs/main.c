#include "../includes/minishell.h"

static void	shell_loop(void);
static char	*set_read_line(t_info *info);

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	// hd_cnt, status라는 변수명만 봤을 때 바로 이해되진 않았다..
	// 전역변수로 사용되는 변수명이니 조금만 더 구체적이면 좋았을 것 같다.
	g_var.hd_cnt = 0;
	g_var.status = 0;
	g_var.old_std_fdin = dup(STDIN_FILENO);
	g_var.old_std_fdout = dup(STDOUT_FILENO);
	g_var.env_list = get_envp_list(envp);
	welcome_screen();
	// display, nodisplay는 각각 제어문자 출력여부에 대한 설정 같다.
	// set_echoctl_on, set_echoctl_off 같은 변수명을 사용했으면,
	// 조금 더 구체적으로 의미가 전달됐을 것 같다.
	if (tcgetattr(STDIN_FILENO, &g_var.display_set) == ERROR)
		error_exit("minsh: tcgetattr");
	if (tcgetattr(STDIN_FILENO, &g_var.nodisplay_set) == ERROR)
		error_exit("minsh: tcgetattr");
	g_var.nodisplay_set.c_lflag &= ~ECHOCTL;
	ft_display_ctrlx_set(NODISPLAY);
	shell_loop();
}

static void	shell_loop(void)
{
	t_info	info;
	char	*cmd_line;

	while (1)
	{
		// 현재는 매 루프마다 dup2를 호출하는데, 만약 fork를 통해 수행되는 명령어라면,
		// dup2를 매번 호출할 필요는 없을 것 같다.
		dup2(g_var.old_std_fdin, STDIN_FILENO);
		dup2(g_var.old_std_fdout, STDOUT_FILENO);
		cmd_line = set_read_line(&info);
		add_history(cmd_line);
		// exec_set함수에서 너무 많은 일이 일어나는 것 같다.
		// 이를 포괄하는 함수명을 짓는 건 쉽지 않을 것 같다.
		// main에서 각 절차를 확인할 수 있도록 쪼개두었으면 좋았을 것 같다.
		exec_set(cmd_line);
	}
}

static char	*set_read_line(t_info *info)
{
	char	*line;

	signal(SIGINT, sig_readline);
	signal(SIGQUIT, SIG_IGN);
	// h_token을 왜 널로 초기화해주는거지..?
	info->h_token = NULL;
	line = readline("minish$ ");
	if (!line)
	{
		ft_putstr_fd("\033[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[7C", STDOUT_FILENO);
		ft_putstr_fd(" exit\n", STDOUT_FILENO);
		ft_display_ctrlx_set(DISPLAY);
		exit(g_var.status);
	}
	return (line);
}
