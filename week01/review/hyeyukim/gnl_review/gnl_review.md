# get_next_line(jibang) code review

### get_next_line

```c
char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	// 에러 처리
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// 개행이나 EOF 나오기 전까지 파일 읽고 save에 저장
	save = read_newline(fd, save);
	if (!save)
		return (NULL);
	// 개행 나올 때까지 내지는 EOF 나오기 직전까지의 내용을 line에 저장
	line = get_one_line(save);
	// 개행 나온 직후부터의 내용 save에 저장
	save = get_remains(save);
	return (line);
}
```

1. 함수 설명
	- 인자: 
		- int fd = 파일의 파일 디스크립터 값
	- 반환값: 
		- char *line = 파일에서 읽은 줄의 문자열 포인터
	- 설명:
	해당 파일의 현재 offset으로부터 개행이 나오거나 EOF가 나오기 전까지를 하나의 문자열에 저장하고 해당 문자열의 포인터를 반환하는 함수이다.
	읽은 파일에 개행이 있을 경우 개행을 포함한 문자열을 반환한다.

2. logic
	1) 에러 처리
		fd < 0이거나 BUFFER_SIZE <0인 경우 NULL을 반환한다.
	2) read_newline
		개행, EOF가 나올때까지 주어진 버퍼 사이즈만큼 파일을 읽고 읽은 부분은 문자열 save에 저장한다.
	3) get_one_line
		개행이 나온 직후 내지는 EOF가 나오기 전까지를 반환할 문자열 line에 저장한다.
	4) get_remains
		개행이 나온 직후의 문자들을 문자열 save에 저장한다.

3. comment
	logic이 간단해서 코드의 전반적인 흐름을 이해하기 쉬웠다.
	get_next_line 서브젝트의 주요 함수인 get_next_line만 보아도 해당 함수가 어떤 일을 하는지 바로 파악할 수 있어서 가독성이 좋았다고 생각된다.
	아쉬운 점이 있다면 문자열의 처음부터 끝까지 순차적으로 확인하는 부분이 많았다는 점이다.
		read_newline 함수 내에서 문자열에 개행이 있는지 확인할 때,
		read_newline 함수 내에서 두 문자열을 하나의 문자열로 합칠 때,
		get_one_line 함수 내에서 개행이 있는 위치를 파악할 때,
		get_one_line 함수 내에서 save에 있는 문자들을 line에 복사할 때,
		get_remains 함수 내에서 개행이 있는 위치를 파악할 때,
		get_remains 함수 내에서 save에 있는 문자들을 remains에 복사할 때,
	코드 전체에서 총 6번 해당 부분이 있는 것으로 파악되는데 해당 부분의 횟수를 조금 줄일 수 있다면 보다 더 좋은 성능을 가진 get_next_line 함수를 구현할 수 있을 것이라 생각된다.

### 세부 함수

#### read_newline

```C
char	*read_newline(int fd, char *save)
{
	char	*buff;
	int		read_idx;

	// 버퍼로 사용할 공간 할당
	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_idx = 1;
	// 저장한 문자열에 개행이 있거나 읽은 바이트 수가 0(즉 EOF가 나올때까지)이 나올때까지 반복해서 파일 읽기
	while (!is_newline(save) && read_idx != 0)
	{
		read_idx = read(fd, buff, BUFFER_SIZE);
		if (read_idx == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_idx] = '\0';
		// 파일에서 추가로 읽은 내용 SAVE에 업데이트하기
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}
```

1. 함수 설명
	- 인자: 
		- int fd = 파일의 파일 디스크립터 값
		- char *save = 읽었지만 반환한 문자열에 포함되지 않은 문자들의 문자열
	- 반환값:
		- char *save = 읽은 문자들을 저장한 문자열
	개행이나 EOF가 나오기 전까지 계속해서 파일을 읽고 save 문자열에 이어붙인다.

2. comment
	해당 함수에서 다음과 같은 부분들이 아쉬웠다.
	1) buff 문자열에 동적할당을 사용한 점
		buff 문자열은 read_newline 함수 내에서만 사용된다.
		따라서 동적할당을 하기보다는 정적 배열을 사용했으면 좋았을 것 같다.
	2) 에러 처리
		해당 함수에는 두 가지 사항에 대해 에러처리하였다.
		첫 번째 할당을 실패했을 경우
		두 번째 read 함수를 실패했을 때, 즉 read 함수의 반환값이 -1일 경우
		각 에러가 발생할 경우 NULL을 반환하는데 그 이전에 save를 free하지 않은 점이 아쉽다.
	3) is_newline 함수명
		주어진 문자열에 개행이 있는지 없는지를 판단하는 함수인데 함수명만 보면 주어진 문자가 개행인지 아닌지를 판단하는 함수처럼 이해된다.
		exist_newline과 같은 함수명으로 수정하면 코드의 흐름을 따라가기 보다 더 수월해질 것 같다.
	4) read_idx 변수명
		read_idx는 read_index의 줄임말로 이해된다.
		해당 변수에 read 함수의 반환값, 파일로부터 읽은 바이트 수를 저장하고 있다.
		따라서 index보다는 bytes라는 변수명이 보다 자연스럽지않을까라는 생각이 든다.

#### get_one_line

```C
char	*get_one_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	// EOF 나오면 NULL 저장
	if (save[i] == '\0')
		return (NULL);
	// EOF나 줄바꿈 나올때까지 인덱스 밀기
	while (save[i] && save[i] != '\n')
		i++;
	// 줄바꿈과 '\0' 고려해서 할당하기
	line = (char *) malloc(sizeof(char) * (i + 1 + 1));
	if (!line)
		return (NULL);
	i = 0;
	// 줄바꿈 전까지 내용 복사
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	// 줄바꿈 있으면 줄바꿈 추가
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	// 마지막에 널문자 추가
	line[i] = '\0';
	return (line);
}
```

1. 함수 설명
	- 인자:
		- char *save = 파일에서 읽은 문자들을 저장한 문자열
	- 반환값: save에 저장된 문자들중 일부를 하나의 문자열에 저장하고 핻아 문자열의 포인터를 반환한다.
	save에 개행 문자가 있으면 개행까지의 문자들을 하나의 문자열에 저장하고 해당 문자열의 포인터를 반환한다.
	만약 save에 개행 문자가 없는 경우 save에 저장된 모든 문자들을 하나의 문자열에 저장하고 해당 문자열의 포인터를 반환한다.
		

2. comment
	함수명이 직관적이어서 좋은 것 같다.
	save에 저장된 문자들로부터 딱 한 줄을 얻어온다는 의미가 잘 산 것 같다.
	다만 malloc을 통한 동적 할당을 실패할 때 save를 free한 후 NULL을 채워야 메모리 누수가 방지될 것 같다.
	물론 save를 NULL로 바꾸기 위해서는 인자로 단일 포인터가 아니라 이중 포인터를 사용해야할 것 같다.

#### get_remains
```C
char	*get_remains(char *save)
{
	char	*remains;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	// 줄바꿈이나 EOF 나올때까지 인덱스 밀기
	while (save[i] && save[i] != '\n')
		i++;
	// EOF 나왔으면 그냥 NULL 저장
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	// 동적할당
	len = ft_strlen(save);
	remains = (char *) malloc(sizeof(char) * (len - (i + 1) + 1));
	if (!remains)
		return (NULL);
	i++;
	j = 0;
	// 내용 복사
	while (save[i])
		remains[j++] = save[i++];
	remains[j] = '\0';
	free(save);
	return (remains);
}
```

1. 함수 설명
	- 인자:
		- char *save = 파일에서 읽은 문자들을 저장한 문자열
	- 반환값: save에 저장된 문자들중 일부를 한 문자열에 저장하고 해당 문자열의 포인터를 반환한다.
	save에 개행 문자가 있으면 개행 이후의 문자들을 하나의 문자열에 저장하고 해당 문자열의 포인터를 반환한다.
	만약 save에 개행 문자가 없는 경우 NULL을 반환한다.

2. comment
	malloc을 통한 동적 할당을 실패할 때 save를 free한 후 NULL을 채워야 메모리 누수가 방지될 것 같다.

#### ft_strjoin

```C
char	*ft_strjoin(char *save, char *buff)
{
	char	*join;
	size_t	len_s;
	size_t	len_b;

	// save가 NULL인 경우 빈 문자열 할당
	if (save == NULL)
	{
		save = (char *) malloc(sizeof(char) * 1);
		save[0] = '\0';
	}
	// 둘 다 NULL인 경우에는 NULL 반환
	if (save == NULL && buff == NULL)
		return (NULL);
	// 두 문자열의 길이의 합과 널문자 고려해서 할당하기
	len_s = ft_strlen(save);
	len_b = ft_strlen(buff);
	join = (char *) malloc(sizeof(char) * (len_s + len_b + 1));
	if (!join)
		return (NULL);
	// 내용 복사
	ft_joinlcpy(join, save, len_s + 1);
	ft_joinlcpy(join + len_s, buff, len_b + 1);
	free(save);
	return (join);
}

```

1. comment
	standard library에 있는 strjoin에서 변형된 부분이 있으므로
	get_next_line를 구현할 때만 사용하는 strjoin이라는 점이 부각되면 좋을 것 같다.
	또한, NULL 가드에서 둘 다 NULL이 들어온 경우에 그냥 NULL을 반환하는 조건문의 경우에는 if (save == NULL) 조건문 위로 위치를 변경해야할 것 같다. 아니면 메모리 누수가 발생할 수 있을 것으로 보이기 때문이다.
	```C
	if (save == NULL && buff == NULL)
		return (NULL);
	if (save == NULL)
	{
		save = (char *) malloc(sizeof(char) * 1);
		save[0] = '\0';
	}
	```
	또한 NULL 가드하고 나서 NULL 반환하기 이전에 save를 free해줘야할 것 같다.
	```c
		join = (char *) malloc(sizeof(char) * (len_s + len_b + 1));
	if (!join)
	{
		free(save);
		return (NULL);
	}
	```