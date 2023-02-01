CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAG = -L./ -lmlx -framework OpenGL -framework AppKit

NAME	= fdf
BONUS	= fdf_bonus
LIBFT	= libft.a
LIBMLX	= libmlx.dylib

INC_DIR 		= includes
SRC_DIR			= srcs
SRCS_BONUS_DIR	= srcs_bonus
LIBFT_DIR		= libft
MLX_DIR			= minilibx_mms_20210621

SRCS = draw_utils.c\
	   ft_perror_exit.c\
	   ft_syscalls.c\
	   main.c\
	   map_parser.c\
	   mlx_interface.c\
	   rotation.c\
	   key_hook.c\
	   projection.c\
	   render_frame.c

SRCS_BONUS = draw_utils_bonus.c\
			 ft_perror_exit_bonus.c\
			 ft_syscalls_bonus.c\
			 key_hook_bonus.c\
			 main_bonus.c\
			 map_parser_bonus.c\
			 mlx_interface_bonus.c\
			 projection_bonus.c\
			 render_frame_bonus.c\
			 rotation_bonus.c\

OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(SRCS_BONUS_DIR)/, $(SRCS_BONUS:.c=.o))

$(NAME): $(OBJS)
	make all -C $(LIBFT_DIR)
	make all -C $(MLX_DIR)
	cp $(MLX_DIR)/$(LIBMLX) ./
	$(CC) $(CFLAGS) $(MLXFLAG) $^ $(LIBFT_DIR)/$(LIBFT) -o $@

$(BONUS): $(OBJS_BONUS) 
	make all -C $(LIBFT_DIR)
	make all -C $(MLX_DIR)
	cp $(MLX_DIR)/$(LIBMLX) ./
	$(CC) $(CFLAGS) $(MLXFLAG) $^ $(LIBFT_DIR)/$(LIBFT) -o $@

all: $(NAME)

bonus: $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	make clean -C $(LIBFT_DIR) 
	make clean -C $(MLX_DIR)
	rm -f $(OBJS) $(OBJS_BONUS) $(LIBMLX)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(NAME) $(BONUS) $(LIBMLX)

re: 
	make fclean
	make all

.PHONY: clean fclean re all bonus
