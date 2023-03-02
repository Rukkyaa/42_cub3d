/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/02 21:48:19 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "../mlx/mlx/mlx.h"
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "../includes/miniaudio.h"

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
# define SHIFT 65505


# define FOV_RADIANS ( M_PI / 2 )
# define FOV 60

# define RES_X  1280
# define RES_Y  720

// # define RES_X  1920
// # define RES_Y  1080

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

typedef struct s_sound
{
	ma_decoder			decoder;
	ma_device_config	device_config;
	ma_device			device;
}				t_sound;

typedef struct s_sounds
{
	t_sound	footstep;
	t_sound	dejavu;
}				t_sounds;

typedef struct t_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_vector3d
{
	double			x;
	double			y;
	double			z;
}					t_vector3d;

typedef struct s_camera
{
	float	proj_plane_distance;
	float	proj_plane_height;
	float	proj_plane_width;
}					t_camera;

typedef struct s_player
{
	t_vector	pos;
	t_vector	speed;
	t_vector3d	pos3d;
	t_vector	collision_pos;
	t_vector	direction;
	float		direction_adjust;
	t_vector	current_tile;
}				t_player;

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

// TEXTURE
typedef struct s_texture
{
	t_img	wall1;
	t_img	wall2;
	t_img	wall3;
	t_img	wall4;
	t_img	ground;
	t_img	roof;
	int		text_heigth;
	int		text_width;
}				t_texture;

typedef struct s_collision
{
	t_vector		point;
	t_img			wall;
	char			orientation;
	float			distance;
	float			x_pos_tex;
}					t_collision;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*fps_win;
	int			time_inc;
	t_img		img;
	t_img		fps_img;
	char		**map;
	int				key_states[256];
	int				key_release_states[256];
	t_vector	mouse;
	t_player	player;
	t_texture	texture;
	t_sounds	sounds;
	t_camera	camera;
	t_vector	v_up;
	t_vector	v_down;
	t_vector	v_left;
	t_vector	v_right;
}				t_game;

// Ray casting
t_collision	cast_2D_ray(t_game *game, t_vector direction);

// Render
void	img_pix_put(t_img *img, int x, int y, int color);
void    render_fps(t_game *game);
void	clear_img(t_img *img);
int		get_color(t_img *img, int x, int y);
int		is_wall(char c);
void	get_wall(t_game *game, t_collision *collision, char c);
void	wall_render(t_game *game, t_collision collision, t_vector line_pos, double line_height);


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

// Controls
t_vector	get_next_tile(t_game *game, t_vector direction);


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

/*****************************************************************
** $$\    $$\ $$$$$$$$\  $$$$$$\ $$$$$$$$\  $$$$$$\  $$$$$$$\   **
** $$ |   $$ |$$  _____|$$  __$$\\__$$  __|$$  __$$\ $$  __$$\  **
** $$ |   $$ |$$ |      $$ /  \__|  $$ |   $$ /  $$ |$$ |  $$ | **
** \$$\  $$  |$$$$$\    $$ |        $$ |   $$ |  $$ |$$$$$$$  | **
**  \$$\$$  / $$  __|   $$ |        $$ |   $$ |  $$ |$$  __$$<  **
**   \$$$  /  $$ |      $$ |  $$\   $$ |   $$ |  $$ |$$ |  $$ | **
**    \$  /   $$$$$$$$\ \$$$$$$  |  $$ |    $$$$$$  |$$ |  $$ | **
**     \_/    \________| \______/   \__|    \______/ \__|  \__| **
*****************************************************************/

t_vector	vec_sum(t_vector vec1, t_vector vec2);
t_vector	vec_mult(t_vector vec1, t_vector vec2);
t_vector	vec_scalar_mult(t_vector vec1, double i);
t_vector	vec_normalize(t_vector vec);
t_vector	vec_rotate(t_vector vector, float angle);
void		vec_to_angle(double angle, t_vector *vector);
void		vec_print(t_vector *vector, char *name);
void		vec_rotate_rad(t_vector *vector, float angle);
void		vec_rotate_edit(t_vector *vector, float angle);
double		vec_distance(t_vector vec1, t_vector vec2);
double 		vec3d_distance(t_vector3d vec1, t_vector3d vec2);
double		vec_angle(t_vector v1, t_vector v2);

//SOUND
void		load_sounds(t_sounds *sounds);
void		clear_sounds(t_sounds *sounds);
int			player_moving(t_game *game);

#endif
