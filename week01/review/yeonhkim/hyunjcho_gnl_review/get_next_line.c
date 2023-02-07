#include "get_next_line.h"

int	ft_strlen(char	*s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

void	ft_memmove(char	*s, int len)
{
	int	j;
	int	i;

	i = -1;
	j = len;
	while (++i < BUFFER_SIZE - len)
		s[i] = s[j++];
	while (i < BUFFER_SIZE)
		s[i++] = 0;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_ret;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_ret = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_ret)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		new_ret[i] = s1[i];
	j = -1; 
	while (++j < s2_len)
		new_ret[i + j] = s2[j];
	free(s1);
	ft_memmove(s2, s2_len);
	return (new_ret);
}

int	ft_strchr(char *s)
{
	while (*s && *s != '\n')
		s++;
	if (*s == '\n')
		return (0);
	return (1);
}

// ft_로 시작하는 함수들 각자가 대부분 원본 함수에서 변형된 형태인데 같은 이름을 사용헤 아쉽다.

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1]; // 정의한 버퍼 사이즈보다 왜 1 더 많이 할당하지? BUFFER_SIZE의 버퍼가 이 buffer가 맞는 것 같은데...버퍼 사이즈가 버퍼 사이즈가 아닌가(?)
	char		*ret;
	int			read_value;	// 무슨 값일까? 데이터 타입을 보면 읽은 바이트(문자)는 아닌 것 같은데...

	if (fd < 0 || BUFFER_SIZE <= 0)	// 앞에서 바로 예외 처리를 해주는구나. 버퍼 사이즈 관련 예외 처리도 있는 것을 보면 버퍼 사이즈를 개발자가 정의한 값 외의 값으로 바꿀 수 있나보군.
									// (헤더 파일 읽고 옴...) 헤더에 BUFFER_SIZE 정의가 없네...빠뜨리셨나보다
		return (NULL);
	ret = malloc(sizeof(char)); // 왜 하는거지?
	if (!ret)
		return (NULL);
	*ret = 0; // 왜 하지? 22
	// 아! 빈 줄(empty line)이구나.
	// 처음 보는 사람 입장에서는, 무슨 의미인지 파악하기 힘든 듯. 할당 값이 0이 아닌 문자 '\0'이었다면 더 빨리 눈치챘을 것 같음.
	while (ft_strchr(ret)) // 음??? strchr에 인자가 하나밖에 없네. 내가 아는 strchr가 아닌가...
	// 나는 이 함수가 무엇을 하는지 이미 알고있으니, 일단 이해하는데 문제는 없다. 안에서 개행 문자 '\n'가 있는지 확인하는 거겠지.
	{
		if (!buffer[0]) // 버퍼에 들어가있는 것은 문자들이므로 bang 기호보다 '\0'와의 일치 여부를 판별하면 좋을 듯
		{
			read_value = read(fd, buffer, BUFFER_SIZE); // read의 반환 값이 뭘 의미하더라?
			// read_value는 지정한 fd로부터 읽어들인 바이트의 사이즈를 반환하는구나. 
			if (!read_value && ret[0] != 0)
				return (ret);
			else if (read_value < 0 || (!read_value && !ret[0])) 
	// 앞에서 이미 fd값이 유효한지 검사해주었기 때문에 read에 대한 에러 처리는 하지 않아도 되는데, 이 부분은 빼도 될 것 같다.
	// *read는 이미 성공적으로 open되어 유효한 값을 부여받은 fd에 대해 별도의 검사를 하지않고 무조건 0 이상의 값을 리턴하도록 되어있다.
										// 앞의 조건문과 형태가 비슷해서 헷갈린다.
										// 예외 처리이므로 앞선 조건문보다 먼저 확인하는게 좀더 좋을 것 같음.
			{
				free(ret);
				return (NULL);
			}
		}
		ret = ft_strjoin(ret, buffer);
		if (!ret)
			return (NULL);
	}
	return (ret);
}