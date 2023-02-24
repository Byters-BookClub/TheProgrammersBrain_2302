/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:33:26 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/24 00:03:45 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_error.h"
#include "heredoc_manager.h"
#include "parser_internal.h"

int	parser(t_token *tokens, t_node **parse_tree) //아하.. 이부분은 트리구조를 만들어줘서 파싱을 완성해주는 함수구나.. 이름을 좀만 바꿔줬으면 더 좋았겠다
{
	int		res;
	int		offset;

	*parse_tree = create_tree_node(parse_tree);
	if (tokens[0].type == TOKEN_NONE)
	{
		(*parse_tree)->type = NODE_NONE;
		return (SUCCESS);
	}
	offset = 0;
	heredoc_init(*parse_tree);
	res = parse_list(*parse_tree, tokens, &offset); // 여기서 리스트 형태로 넣어 주나..? 이름은 왜 트리지? 트리노드 left가 firstchild, right가 sibling같은데..음..생각해보니 아마 토큰리스트를 파싱해서 트리에 넣어준다는 것이겠구나
	if (heredoc_stat_get() == HEREDOC_INTSIG)
	{
		return (FAILURE);
	}
	if (res == FAILURE || tokens[offset].type != TOKEN_NONE)
	{
		handle_syntax_error(tokens[offset]);
		return (FAILURE);
	}
	return (SUCCESS);
}
