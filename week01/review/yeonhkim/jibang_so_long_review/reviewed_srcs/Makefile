# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 13:35:07 by jibang            #+#    #+#              #
#    Updated: 2022/07/02 20:25:58 by jibang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -framework OpenGL -framework AppKit
NAME = so_long
LIBA = libft.a
MAKE = make
SRCS =	./so_long.c \
		./solong_utils.c \
		./map_parse.c \
		./movement.c \
		./image_paint.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBA)
	@$(CC) $(CFLAGS) $(SRCS) $(MLXFLAGS) ./minilibx_opengl_20191021/libmlx.a ./libft/libft.a -o $(NAME)

$(LIBA):
	make all -C ./libft/

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME2)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
