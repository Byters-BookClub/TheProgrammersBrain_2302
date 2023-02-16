NAME	= libgnl.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

SRCS	=					\
		get_next_line.c		\
		get_next_line_utils.c

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
