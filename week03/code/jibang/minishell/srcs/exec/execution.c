#include "../../includes/minishell.h"

// exec_set함수에서 너무 많은 일이 일어나는 것 같다.
// 이를 포괄하는 함수명을 짓는 건 쉽지 않을 것 같다.
// main에서 각 절차를 확인할 수 있도록 쪼개두었으면 좋았을 것 같다.

// 이 함수 반환값을 사용하지 않는 것 같다..
int	exec_set(char *cmd_line)
{
	int		status;
	t_info	info;

	status = EXIT_SUCCESS;
	info.h_token = NULL;
	// 토크나이징, 확장, asterisk 처리를 여기서 전부 하나보다
	// 하나 궁금한 건, h접두사는 왜 붙었지? (히어독으로 추정됨)
	tokenizer(&(info.h_token), cmd_line);
	expand(&(info.h_token));
	aster_replace(&(info.h_token));
	// 만약 신택스 에러가 없고, heredoc 리다이렉션이 정상수행되면 명령어 실행
	if (check_syntax_error(info.h_token) == SUCCESS && \
		redir_here_doc_check(&info) == SUCCESS)
	{
		// 변수길이 때문에 r_node라고 적은 것이라면 root가 낫지 않았을까? 싶음.
		// left, right와 혼동의 여지가 있다고 생각됨
		// 로직상 create와 set이 분리되어있다. 
		// create에서는 동적할당만 수행하기에, set_btree_node 함수내에서 호출해도 괜찮았을 것 같다
		info.r_node = create_btree_node(info.h_token);
		set_btree_node(&(info.r_node));
		ft_display_ctrlx_set(DISPLAY);
		status = execution(&info);
		ft_display_ctrlx_set(NODISPLAY);
		free(cmd_line);
	}
	else
		delete_token(info.h_token);
	redir_unlink();
	return (status);
}

int	execution(t_info *info)
{
	int	status;

	status = EXIT_SUCCESS;
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	status = execute_btree_node(info, info->r_node);
	delete_node(info->r_node);
	return (status);
}

// root가 명령어의 종류의 타입을 갖고있는 거 같다
// exec를 세가지로 나눠둔 이유를 잘 모르겠다..?
// 이를 파악하려면 tree구조를 더 자세히 알야아할 것 같다

// 인풋명령어에 파이프가 있으면 루트 타입이 pipe가 되는걸로 추정된다
// 개인적으로 이를 루트노드의 타입으로 처리하는 건 조금 어색한 것 같다
int	execute_btree_node(t_info *info, t_tree_node *root)
{
	if (!root)
		return (EXIT_FAILURE);
	if (root->type == TN_WORD)
		g_var.status = exec_word(root);
	else if (root->type == TN_PARENS)
		g_var.status = exec_parens(root);
	else if (root->type == TN_AND || root->type == TN_OR)
		exec_and_or(info, root);
	else if (root->type == TN_PIPE)
		g_var.status = exec_pipe(root);
	return (g_var.status);
}
