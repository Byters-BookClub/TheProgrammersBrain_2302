# ================ Color Variables ================ #
BLACK			= 	"\033[0;30m"
GRAY			= 	"\033[1;30m"
RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[1;33m"
PURPLE			=	"\033[0;35m"
CYAN			=	"\033[0;36m"
WHITE			=	"\033[1;37m"
EOC				=	"\033[0;0m"
LINE_CLEAR		=	"\x1b[1A\x1b[M"
# ================================================= #

NAME			= minishell

CC				= cc
CFLAGS			= -g3 -fsanitize=address -Wall -Wextra -Werror
RM				= rm -rf

LIB_READ		= -l readline
LDFLAGS			= -L$(shell brew --prefix readline)/lib
CPPFLAGS		= -I$(shell brew --prefix readline)/include

LIB_DIR			= lib/
LIBFT			= libft/libft.a
GNL				= get_next_line/libgnl.a
FTPRINT			= ft_printf/libftprintf.a
HEADERS			= includes

BUILTIN			= ft_echo ft_export ft_unset ft_env ft_pwd ft_cd ft_exit
ENV				= environ get_envnode
EXEC			= execution exec_and_or exec_parens exec_pipe exec_word
EXPAN			= wildcard wildcard_utils wildcard_caseby
PARSER			= tokenizer check_tokens set_btree
REDIRECTION		= redirection redir_here_doc
UTILS			= util_buff util_builtin util_error util_exec util_expand util_redirection util_signal util_token util_tree utils welcome_screen
MAIN			= main

SRCS 			= $(addsuffix .c, $(addprefix srcs/, $(MAIN)))			\
				$(addsuffix .c, $(addprefix srcs/env/, $(ENV)))			\
				$(addsuffix .c, $(addprefix srcs/exec/, $(EXEC)))		\
				$(addsuffix .c, $(addprefix srcs/expan/, $(EXPAN)))		\
				$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))		\
				$(addsuffix .c, $(addprefix srcs/parser/, $(PARSER)))	\
				$(addsuffix .c, $(addprefix srcs/builtin/, $(BUILTIN)))	\
				$(addsuffix .c, $(addprefix srcs/redirection/, $(REDIRECTION)))

OBJS 			= $(SRCS:c=o)
all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN) "Source files are compiled!\n" $(EOC)
	@make -j -C $(LIB_DIR)/libft
	@make -j -C $(LIB_DIR)/ft_printf
	@make -j -C $(LIB_DIR)/get_next_line
	@$(CC) $(CFLAGS) -o $@ $^ $(LIB_DIR)/$(LIBFT) $(LIB_DIR)/$(GNL) $(LIB_READ) $(LDFLAGS) $(CPPFLAGS)
	@make -j fclean -C $(LIB_DIR)/libft
	@make -j fclean -C $(LIB_DIR)/ft_printf
	@make -j fclean -C $(LIB_DIR)/get_next_line
	@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

%.o: %.c $(HEADERS)/$(NAME).h
	@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
	@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@echo $(YELLOW) "Cleaning object files..." $(EOC)
	@$(RM) $(OBJS)
	@echo $(RED) "Object files are cleaned!\n" $(EOC)

fclean:	clean
	@echo $(YELLOW) "Removing $(NAME)..." $(EOC)
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) is removed!\n\n" $(EOC)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
