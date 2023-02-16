NAME	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

SRCS	=							\
		ft_printf.c					\
		ft_putstr_len.c				\
		ft_putnbr_len.c				\
		ft_putchar_len.c			\
		ft_putnbr_unsign.c			\
		ft_putnbr_base_len.c		\
		ft_print_mem_address_len.c

OBJS	= $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar crus $@ $(OBJS)

all : $(NAME)

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : 
	@make fclean 
	@make all

.PHONY: all clean fclean re