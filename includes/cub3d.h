/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 11:14:43 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx/mlx.h"
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define ESC 65307
# define A 97
# define W 119
# define D 100
# define S 115
# define RIGHT 65361
# define LEFT 65363

// COLORS
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define BLACK_PIXEL 0x000000

typedef struct vector
{
	double			x;
	double			y;
}					t_vector;


typedef struct s_player
{
	t_vector	pos;
	t_vector	direction;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int				key_states[256];
	int				key_release_states[256];
	t_player	player;
}				t_game;

// Shapes
void 	draw_circle(t_game *game, t_vector center, int radius, int color);
void	draw_square(t_game *game, int x, int y, int width, int color);
void	draw_vertical_line(t_game *game, int x, int y, int len, int color);
void 	draw_line(t_game *game, t_vector posA, t_vector posB, int thickness, int color);
void    draw_filled_circle(t_game *game, t_vector center, int radius, int color);

// Events 
int		key_gestion(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_keypress(int keycode, t_game *game);
int 	handle_key_state(void *g);


void	draw_player(t_game *game, int color);
void	var_init(t_game *game);
char	**get_map(char *arg);
int		close_window(t_game *game);
void	move(t_game *game, char direction);

#endif
