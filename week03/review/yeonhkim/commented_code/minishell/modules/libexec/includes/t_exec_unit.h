/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_unit.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/02/24 13:55:18 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  T_EXEC_UNIT_H
# define T_EXEC_UNIT_H

enum	e_redirtype	// 음...중간에 언더바(_)가 있는게 좋았을 듯. (혹시 내가 실수로 없앤건가?)
{
	REDIR_NONE = 0,
	REDIR_IN,
	REDIR_OUT,
	REDIR_IN_HERE,
	REDIR_OUT_APPEND,
};
// 각 타입의 입출력 여하에 따라 IN과 OUT이 공통적으로 붙어있으니 통일성이 있어서 보기 좋다.

typedef struct s_redir
{
	int		type;
	char	*content;
}	t_redir;

typedef struct s_exec_unit
{
	char	**argv;		// 오, argv[0]에 command 이름이 있으니 굳이 command name 멤버가 따로 없구나.
						//나는 이 점을 간과해서 command name 멤버가 따로 있었는데...배우고 간다.
	t_redir	*redir_arr;
// unit 배열의 변수명은 units라고 이름 붙였는데 redir는 redir_arr이다. 일관성 있게 접미사를 _arr 혹은 s 둘 중 하나로 통일 시켰으면 좋았을 것 같다.
	int		n_redir;
	int		n_word;		// 이게 뭐지? 바로 위쪽에 n_redir가 있는 것으로 보아서 argv(인자, 옵션)의 개수인 것 같긴한데...
						// 이것만 보고는 잘 모르겠다. 근데 아마도 맞는 것 같다.
						// word token에서 그대로 이름을 따온 것 같은데...word token은 인자(argv)뿐만 아니라 redir도 있기 때문에 적절한 변수명은 아닌 것 같다.
}	t_exec_unit;	

typedef struct s_unit_arr
{
	t_exec_unit	*arr;
	int			n_unit;	// n_unit도 좋은 멤버명이지만, 사실 이 데이터 타입의 이름을 생각해보면 굳이 멤버명에 unit이라는 이름을 끼울 필요가 없다고 생각한다.
						// 왜냐하면 이 구조체의 변수명은 타입명과 거의 동일하게 갈 것이기 때문이다.
						// 예를 들어 't_unit_arr' 타입의 변수명은 'unit_arr' 혹은 'units'가 될 것이다.
						// 그래서 cnt 정도로도 충분할 것이다. 왜냐면 실제로 사용할 때는 'units->cnt' 이렇게 접근하게 될 것이기 때문에.
}	t_unit_arr;
// 데이터 타입 t_exec_unit의 배열(array)임에도 불구하고 exec_라는 접두어 없이 t_unit_arr라서 혼동의 여지가 있다.
// 길더라도 t_exec_unit_arr로 가거나 아니면 t_exec_units 이런 이름이 좋지 않았을까 싶다.

#endif
