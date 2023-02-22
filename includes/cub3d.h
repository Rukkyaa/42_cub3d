/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/22 12:00:55 by teliet           ###   ########.fr       */
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
# include "../mlx/mlx/mlx_int.h"
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

# define ESC 65307
# define A 97
# define W 119
# define D 100
# define S 115
# define RIGHT 65361
# define LEFT 65363


# define FOV_RADIANS ( M_PI * 2 / 3  )
# define FOV 60

# define RES_X  1280
# define RES_Y  720

# define MAX_DISTANCE 10

// COLORS
# define RED_PIXEL   0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL  0x0000FF
# define BLACK_PIXEL 0x000000
# define WHITE_PIXEL 0xFFFFFF
# define PALE_BLUE 	 0x25F7C6
# define PALE_BLUE_SHADED 	 0x0D5243

// TEXTURE
typedef struct s_texture
{
	t_img_stolen	*wall;
	int				text_height;
	int				text_width;
}				t_texture;

typedef struct vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_collision
{
	t_vector		point;
	char			orientation;
	float			distance;
	float			x_pos_tex;
}					t_collision;

typedef struct s_player
{
	t_vector	pos;
	t_vector	direction;
	int			direction_adjust;
	t_vector	current_tile;
}				t_player;

typedef struct	s_img_stolen
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}				t_img_stolen;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
	int		width;
	int		heigth;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*fps_win;
	t_img		img;
	t_img		fps_img;
	char		**map;
	int				key_states[256];
	int				key_release_states[256];
	t_player	player;
	t_texture	texture;
}				t_game;

// Ray casting
t_collision	cast_2D_ray(t_game *game, t_vector direction);

// Render
void	img_pix_put(t_img *img, int x, int y, int color);
void	clean_map(t_game *game);
void    render_fps(t_game *game);
void	clear_img(t_img *img);

// Shapes
void	draw_square(t_game *game, t_vector pos, int width, int color);
void	draw_filled_square(t_game *game, t_vector pos, int width, int color);

void 	draw_circle(t_game *game, t_vector center, int radius, int color);
void	draw_filled_circle(t_img *img, t_vector mid, int radius, int color);

void	draw_vertical_line(t_game *game, t_vector pos, int len, int color);
void	draw_vertical_line_2(t_img *img, t_vector pos, int len, int color);
void	draw_non_filled_line(t_game *game, int x, int y, int len, int color);
void 	draw_line_dda(t_img *img, t_vector vec1, t_vector vec2, int color);

void	load_grid(t_game *game);
void	load_map(t_game *game);

// Events 
int		key_gestion(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_keypress(int keycode, t_game *game);
int 	game_loop(void *g);

// Vector operations
t_vector 	vec_sum(t_vector vec1, t_vector vec2);
void		rotate(t_vector *vector, float angle);
void		rotate_rad(t_vector *vector, float angle);
t_vector 	vec_scalar_mult(t_vector vec1, double i);
t_vector 	vec_mult(t_vector vec1, t_vector vec2);
void 		angle_to_vector(double angle, t_vector *vector);
void    	print_vector2D(t_vector *vector, char *name);
t_vector	rotate2(t_vector vector, float angle);
t_vector 	normalize(t_vector vec);
double 		vec_distance(t_vector vec1, t_vector vec2);
double 		angle_between_vectors(t_vector v1, t_vector v2) ;

t_vector pixel_to_tile(t_vector vector);
t_vector tile_to_pixel(t_vector tile_coord);
int tile_out_of_bound(t_vector tile_coord, t_game *game);
int pixel_out_of_bound(float x, float y, t_img *image);
void	draw_player(t_game *game, int color);
void	var_init(t_game *game);
char	**get_map(char *arg);
int		close_window(t_game *game);
void	move(t_game *game, char direction);

// mlx Utils
unsigned int img_pix_read(t_img *img, int x, int y);

/**************************************
** $$\      $$\  $$$$$$\  $$$$$$$\   **
** $$$\    $$$ |$$  __$$\ $$  __$$\  **
** $$$$\  $$$$ |$$ /  $$ |$$ |  $$ | **
** $$\$$\$$ $$ |$$$$$$$$ |$$$$$$$  | **
** $$ \$$$  $$ |$$  __$$ |$$  ____/  **
** $$ |\$  /$$ |$$ |  $$ |$$ |       **
** $$ | \_/ $$ |$$ |  $$ |$$ |       **
** \__|     \__|\__|  \__|\__|       **
**************************************/

int		map_heigth(char **map);
int		map_width(char **map);
char	**get_map(char *arg);

#endif
