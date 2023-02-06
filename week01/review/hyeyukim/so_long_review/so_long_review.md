# so_long(jibang) review

## main
```C
int	main(int ac, char **av)
{
	t_params	var;
	int			x;
	int			y;

	// 인자 에러 처리
	if (ac != 2)
		ft_perror_exit("Invalid arg number");
	// 주어진 맵 파싱
	var = ft_map_parsing(&var, av);
	// 맵 내용 유효 검사
	if (find_forbidden_deco(var.map_line) == TRUE)
		ft_perror_exit("Forbidden decorations");
	// 각종 변수 및 mlx 관련 초기화
	var.mlx_ptr = mlx_init();
	x = var.map_width * DOTS;
	y = (var.map_height - 1) * DOTS;
	var.win_ptr = mlx_new_window(var.mlx_ptr, x, y, "jibang");
	var.step = 0;
	var.collect_now = 0;
	// 윈도우에 이미지 그리기
	ft_put_images(var);
	// hook 함수 설정
	mlx_hook(var.win_ptr, KEY_RELEASE, 0, &key_press, &var);
	mlx_hook(var.win_ptr, RED_X, 0, &game_exit, &var);
	mlx_loop(var.mlx_ptr);
	return (0);
}
```
1. 함수 설명
	- 인자
    	- 확장자가 .ber인 파일의 경로명을 인자로 받는다.
	인자로 전달 받은 파일을 열어서 맵을 생성하고 window 화면에 띄운다.
	사용자가 누르는 키나 버튼에 따라서 윈도우 화면이 업데이트되고 사용자는 간단한 미니 게임을 즐길 수 있다.

2. comment
   - 맵 파싱과 관련하여
     - 현재 맵 파싱 함수 내부에서도 유효한 맵인지 검사하는 내용을 포함하고 있다.
     - 그렇다면 find_forbidden_deco 맵의 내용이 유효한지 확인하는 부분도 parsing 내부에서 진행되었으면 어땠을까라는 생각이 든다.
     - 아니면 main에 맵 파싱과 맵 내용 유효 검사를 구분짓는다면 볼 때 보다 전체적인 흐름을 이해하기 쉽도록 find_forbidden_deco라는 함수명을 is_valid_map으로 수정하면 좋을 것 같다. 맵 안의 문자들이 decoration이라는 것을 연상하기 쉽지 않았기 때문이다. (함수명은 지극히 개인적인 의견... 저도 이름을 잘 못지어서...)
   - 초기화와 관련하여
     - main의 전체적인 흐름을 보다 쉽게 이해할 수 있도록 따로 초기화 함수를 하나로 빼면 좋았을 것 같다. 그렇게 되면 main 함수내에서 중요한 역할을 하지 않는 x, y 변수도 뺄 수 있어서 가독성이 좋아질 것 같다.

## 맵 파싱
```c
t_params	ft_map_parsing(t_params *var, char **av)
{
	int		fd;
	char	*line;

	// (void)av;
	// 파일 열기
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		ft_perror_exit("map read error");
	// 파일 읽기
	line = get_next_line(fd);
	if (line == NULL)
		ft_perror_exit("map read error");
	// 파일의 첫번째 줄 var->map_line에 저장
	if (line != NULL)
		get_first_line(var, line);
	while (line != NULL)
	{
		(var->map_height)++;
		line = get_next_line(fd);
		// 파일의 다른 줄까지 포함해서 var->map_line에 저장
		if (line)
			get_other_lines(var, line);
	}
	// 파일 닫기
	close(fd);
	// 맵 내용 유효성 검사1 : wall 확인
	check_map_line_err(var->map_line, var->map_width, var->map_height);
	// 맵 내용 유효성 검사2 : E, C, P 확인
	if (check_map_cep(var->map_line) == ERROR)
		ft_perror_exit("Not enough E, C, P");
	// C 개수 var->collect_goal에 저장
	var->collect_goal = number_of_collection(var->map_line);
	return (*var);
}
```

1. 함수 설명
	- 인자: 
    	- t_params *var = 맵의 정보를 담은 구조체
    	- char **av = main에서 받은 인자 배열
   - 인자로 주어진 맵을 파싱하여 구조체에 저장한다. 이때 wall, E, C, P 등에 오류가 있는지 확인하는 과정을 거친다.

2. comment
   - 동일하게 반복되는 예외를 처리하기 위해 ft_perror_exit을 사용한 부분이 인상적이다. 또 get_first_line, get_other_lines와 같은 함수명도 직관적이서 어떠한 흐름을 가진 함수인지 쉽게 파악할 수 있었다.
   - 아쉬웠던 점은 아래와 같다.
     - get_first_line 함수와 get_other_lines 함수
		```c
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
		```
		위의 코드에서 tmp 변수가 꼭 필요한지 모르겠다.
		또한 ft_substr하뭇와 ft_strdup 함수가 필요한지도 잘 모르겠다.
		```c
		line[var->map_width] = 0;
		var->map_line = line;
		```
		로 작성했으면 동적할당하는 횟수와 동적할당 해제하는 횟수를 좀 줄일 수 있지 않았을까?
		get_other_lines 함수에서도 동일한 의문을 품었다.
		```c
		line[var->map_width] = 0;
		var->map_line = ft_Strjoin(var->map_line, line);
		```
	- 동적할당 실패시 일관되지 않은 예외 처리
    	- get_next_line이 NULL을 반환하는 경우에는 에러처리가 되어있지만
    	- ft_substr, ft_strjoin이 NULL을 반환하는 경우에는 에러처리가 되어있지 않은 점이 아쉽다.
	- number_of_collection 함수
    	- 성능 측면에서 생각해보면 check_map_cep 함수에서 c의 개수는 확인하는 것이 좋았을 것으로 생각된다.
    	-  하지만 가독성 면에서 생각해보면 한 함수에서 너무 많은 일을 하기보다는 세분화되는 것도 좋다고 생각하고 그렇게 무거운 작업이 아니기 때문에 이렇게 분리되어있는 것도 나쁘지는 않다고 생각한다.

## 키 훅

```c
void	move_up(t_params *var)
{
	t_pos	pos;

	// player 현재 위치 찾기
	pos = find_player_pos(*var);
	// 벽이 있으면 아무것도 안함
	if (var->map_line[pos.i - var->map_width] == WALL)
		return ;
	// 공간이 있으면 해당 위치로 이동
	else if (var->map_line[pos.i - var->map_width] == SPACE)
	{
		pos.tmp = var->map_line[pos.i];
		var->map_line[pos.i] = var->map_line[pos.i - var->map_width];
		var->map_line[pos.i - var->map_width] = pos.tmp;
		(var->step)++;
	}
	// C면 이동하고 먹은 개수 늘리고 c는 빈공간으로 변경
	else if (var->map_line[pos.i - var->map_width] == 'C')
	{
		var->map_line[pos.i - var->map_width] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
		(var->collect_now)++;
	}
	// 게임 종료 조건을 만족하면 이동
	else if (check_finish_game(var) == SUCCESS)
	{
		var->map_line[pos.i - var->map_width] = var->map_line[pos.i];
		var->map_line[pos.i] = SPACE;
		(var->step)++;
	}
}

int	key_press(int keycode, t_params *var)
{
	if (keycode == W_KEY)
		move_up(var);
	else if (keycode == S_KEY)
		move_down(var);
	else if (keycode == D_KEY)
		move_right(var);
	else if (keycode == A_KEY)
		move_left(var);
	else if (keycode == ESC_KEY)
		exit(0);
	printf("step : %d\n", var->step);
	ft_put_images(*var);
	return (0);
}
```

1. 함수 설명
   - 인자:
     - int keycode : 키보드 키 번호
     - t_params *var : 맵에 대한 정보를 담은 구조체
   - 각 키보드 키 번호에 따라서 해당 프로그램이 어떤 동작을 취할지 설정해놓은 함수이다.
  
2. comment
	- 함수를 보고 쉽게 어떤 일을 하는 함수인지 파악할 수 있었다.
	- move_up, move_down, move_right, move_left 함수 내부도 반복되는 내용이어서 쉽게 이해할 수 있었다.
	- if문과 else if문을 잘 사용해서 필요한 조건들을 잘 확인해준 것 같다.