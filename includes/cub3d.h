/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 17:57:22 by teliet           ###   ########.fr       */
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
# define WHITE_PIXEL 0x111111

typedef struct vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	direction;
	t_vector	current_tile;
}				t_player;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	char		**map;
	int				key_states[256];
	int				key_release_states[256];
	t_player	player;
}				t_game;

// Ray casting
void	cast_2D_ray(t_game *game);

// Render
void	img_pix_put(t_img *img, int x, int y, int color);
void	clean_map(t_game *game);

// Shapes
void	draw_square(t_game *game, t_vector pos, int width, int color);
void	draw_filled_square(t_game *game, t_vector pos, int width, int color);

void 	draw_circle(t_game *game, t_vector center, int radius, int color);
void    draw_filled_circle(t_game *game, t_vector center, int radius, int color);

void	draw_vertical_line(t_game *game, t_vector pos, int len, int color);
void	draw_non_filled_line(t_game *game, int x, int y, int len, int color);
void 	draw_line(t_game *game, t_vector posA, t_vector posB, int thickness, int color);

void	load_grid(t_game *game);
void	load_map(t_game *game);

// Events 
int		key_gestion(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_keypress(int keycode, t_game *game);
int 	handle_key_state(void *g);

// Vector operations
t_vector vec_sum(t_vector vec1, t_vector vec2);
void	rotate(t_vector *vector, float angle);
t_vector vec_scalar_mult(t_vector vec1, double i);
t_vector vec_mult(t_vector vec1, t_vector vec2);
void 	angle_to_vector(double angle, double* vector);

t_vector pixel_to_tile(t_vector vector);
t_vector tile_to_pixel(t_vector tile_coord);
int tile_out_of_bound(t_vector tile_coord);
int pixel_out_of_bound(float x, float y);
void	draw_player(t_game *game, int color);
void	var_init(t_game *game);
char	**get_map(char *arg);
int		close_window(t_game *game);
void	move(t_game *game, char direction);

#endif
