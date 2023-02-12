/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:01:52 by jibang            #+#    #+#             */
/*   Updated: 2023/02/06 21:28:11 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// 함수명과는 달리 인자로 map의 first line을 받고 있다. 이 함수에서 first line을 반환해주고 있지 않다.
// init_map_info 등 맵의 기초 정보를 구하는 것이라는 의미를 담은 이름으로 변경하는 것이 좋을 것 같다. 
void	get_first_line(t_params *var, char *line)
{
	char	*tmp;

	var->map_height = 1;
	var->map_width = ft_strlen(line) - 1;
	tmp = ft_substr(line, 0, var->map_width);
	var->map_line = ft_strdup(tmp);
	var->width_criteria = var->map_width;
	free(tmp);
	free(line);
}

// 위와 동일하게 함수명과 함수가 하는 기능이 일치하지 않고 있다.
// 함수의 기능에 알맞은 이름을 사용하면 읽기 수월해질 것 같다.
void	get_other_lines(t_params *var, char *line)
{
	char	*tmp;

	var->map_width = ft_strlen(line) - 1;
	if (var->map_width != var->width_criteria)
		ft_perror_exit("wrong map input");
	tmp = ft_substr(line, 0, var->map_width);
	var->map_line = ft_strjoin(var->map_line, tmp);
	free(tmp);
	free(line);
}

// 맵의 유효성(valid)을 검사하는 부분이므로 이 함수가 하는 일을 명확히 명시하기 위해 valid라는 단어를 함수명에 넣는 것이 좋을 것 같다.
	// (개인적으로는, valid_check_map 혹은 is_valid_map 정도)
// 또 반환값은 success/failure가 아닌 true/false가 좋을 것 같다.
	// 맵이 유효하지 않다(invalid)고 판단된 것 또한 어쨌든 valid check에는 성공(success)한 것이기 때문이다. 
int	check_map_line_err(char *line, int width, int height)
{
	int		i;
	int		j;

	i = -1;
	while (++i < width)
	{
		if (line[i] != WALL)
			ft_perror_exit("map error");
	}
	j = 0;
	while (++j < height - 1)
	{
		if (line[i] != WALL || line[i + width - 1] != WALL)
			ft_perror_exit("map error");
		i = i + width;
	}
	while (line[i])
	{
		if (line[i] == '\n')
			return (SUCCESS);
		if (line[i] != WALL)
			ft_perror_exit("map error");
		i++;
	}
	return (SUCCESS);
}

// 음....아까는 main문이라서 괜찮았는데 av가 무엇을 뜻하는지 헷갈리기 시작한다.
// argv는 인덱스 [1] 원소에만 접근하기 때문에 해당 원소의 주소만 보내는 것이 좋을 것 같다.
t_params	ft_map_parsing(t_params *var, char **av)
{
	int		fd;
	char	*line;

	// (void)av;
	fd = open(av[1], O_RDONLY); // 여기에서만 av를 사용하는데 이는 파일의 주소(path)이다. 그래서 파라미터는 'char *path' 정도가 좋지 않을까 싶다
	if (fd <= 0)
		ft_perror_exit("map read error");

	// 이 부분들이 전부 map의 기초 정보를 구하는데 사용되어지고 있다. 
	// init_map_info라는 함수 안에 넣는 것이 좋을 것 같다.
	line = get_next_line(fd);
	if (line == NULL)
		ft_perror_exit("map read error");
	if (line != NULL)						// 정반대되는 케이스 line = NULL을 앞에서 에러 처리 하기 때문에 이 조건문은 없어도 될 것 같다.
		get_first_line(var, line);
	while (line != NULL)
	{
		(var->map_height)++;
		line = get_next_line(fd);
		if (line)
			get_other_lines(var, line);		// get_next_line으로 받은 line을 또 get하는 것이 무슨 의미인걸까?
	}
	close(fd);

	// map의 valid check를 하는 부분은 하나의 함수로 합쳐두는 것이 좋을 것 같다.	
	check_map_line_err(var->map_line, var->map_width, var->map_height);
	if (check_map_cep(var->map_line) == ERROR)
		ft_perror_exit("Not enough E, C, P");

	var->collect_goal = number_of_collection(var->map_line);
	return (*var);
}

// 상단의 ft_map_parsing 함수에서만 호출하고 있는 함수인데, static 함수가 아닌 점
// 그리고 필요없이 헤더 파일에 이 함수의 원형(prototype)이 들어있다는 점이 아쉬움.
int	check_map_cep(char *line)
	// cep가 무엇인가 했는데 아마 collection, exit, player의 약자인 것 같다.
		// 만약 이 프로젝트를 잘 모르는 사람들도 한번에 이해할 수 있도록 단어를 바꾸고싶다면 components 등이 어떨까싶다
	// 무엇을 check한다는 것인지 함수명에 명확히 드러나 있으면 좋을 것 같다.
	// 모든 component의 존재(exist) 여부를 확인한다는 이름이면 좋을 듯?
{
	int		i;
	int		c_flag;	// 접미사로 _flag말고 _exist도 괜찮았을 듯.
	int		e_flag;
	int		p_flag;

	i = 0;
	c_flag = 0;
	e_flag = 0;
	p_flag = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			c_flag = 1;
		else if (line[i] == 'E')
			e_flag = 1;
		else if (line[i] == 'P')
			p_flag = 1;
		i++;
	}
	if (c_flag && e_flag && p_flag)
		return (SUCCESS);
	return (ERROR);
}
