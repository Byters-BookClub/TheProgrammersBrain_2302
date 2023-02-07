#include "get_next_line.h"

static char	*empty_line(void)
{
	char	*line;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	*line = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];	// 버퍼 사이즈 상수값을 이름에 맞게 사용하기
	char		*line; 					// ret -> line, 반환하는 것이 문자열 라인(line)이므로 
	int			r_size; 				// read_value -> r_size

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = empty_line();
	while (!ft_strchr(line, '\n'))		// 개행 문자 '\n'를 찾는다는 것을 명확히 하기
	{
		if (buffer[0] == '\0')
		{
			r_size = read(fd, buffer, BUFFER_SIZE - 1);
			if (r_size == 0)			// 별도의 함수로 빼면 더 좋을 듯.
			{
				if (line[0] == '\0')
				{
					free(line);
					return (NULL);
				}
				else
					return (line);
			}
		}
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}