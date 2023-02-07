/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:36:59 by jibang            #+#    #+#             */
/*   Updated: 2022/07/05 17:03:18 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

/* X_EVNET */
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define MOUSE_PRESS 4
# define MOUSE_RELEASE 5
# define KEY_DESTROY 17

/* map parsing */
# define FIRST_OR_LAST 0
# define MIDDLE 1
# define ERROR -1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0

/* image */
# define WALL '1'
# define SPACE '0'
# define DOTS 64

/* KEY_VALUES */
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define ESC_KEY 53
# define RED_X 17

typedef struct s_string
{
	char	*step;
	char	*col;
	char	*mis;
}	t_string;

typedef struct s_pos
{
	int		i;
	int		j;
	int		check;
	char	tmp;
}	t_pos;

typedef struct s_image
{
	void	*hero;
	void	*bird;
	void	*grass;
	void	*box;
	void	*tile;
}	t_image;

typedef struct s_params
{
	int		x;
	int		y;
	int		step;
	void	*mlx_ptr;
	void	*win_ptr;
	int		map_width;
	int		map_height;
	int		width_criteria;
	char	*map_line;
	int		collect_goal;
	int		collect_now;
}	t_params;

void		ft_perror_exit(char *s);

/* UTILS */
t_pos		find_player_pos(t_params var);
int			check_finish_game(t_params *var);
int			number_of_collection(char *map_line);
int			find_forbidden_deco(char *line);
int			check_e_finished(t_params var);

/* MOVEMENT */
void		move_up(t_params *var);
void		move_down(t_params *var);
void		move_right(t_params *var);
void		move_left(t_params *var);
int			key_press(int keycode, t_params *var);

/* MAP PARSING */
t_params	ft_map_parsing(t_params *var, char **av);
int			check_map_line_err(char *line, int width, int height);
int			check_map_cep(char *line);

/* IMAGES */
void		ft_put_images(t_params var);
void		put_info(t_params var);

#endif
