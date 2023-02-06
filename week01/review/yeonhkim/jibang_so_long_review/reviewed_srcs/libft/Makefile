CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
OBJS = $(SRCS:.c=.o)
	SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
		   ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		   ft_strncmp.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_memchr.c \
		   ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		   ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		   ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		   ft_printf.c get_next_line.c \
		   ./ft_printf/ft_print_mem_address_len.c ./ft_printf/ft_putchar_len.c ./ft_printf/ft_putnbr_len.c \
		   ./ft_printf/ft_putstr_len.c ./ft_printf/ft_putnbr_base_len.c ./ft_printf/ft_putnbr_unsign.c \
		   ./get_next_line/get_next_line_utils.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar crus $@ $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
