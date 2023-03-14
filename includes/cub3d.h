/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/13 16:45:11 by teliet           ###   ########.fr       */
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
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

# define ESC 65307
# define A 97
# define W 119
# define D 100
# define S 115
# define RIGHT 65361
# define LEFT  65363
# define SHIFT 65505


# define FOV_RADIANS ( M_PI / 3)
# define FOV 60

# define RES_X  1920
# define RES_Y  1200

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

typedef struct vector
{
	double			x;
	double			y;
}					t_vector3d;

typedef struct s_vector3d
{
	double			x;
	double			y;
	double			z;
}					t_vector3d;

typedef struct s_collision
{
	t_vector3d		point;
	char			orientation;
	float			distance;
	float			x_pos_tex;
}					t_collision;

typedef struct s_player
{
	t_vector3d	pos;
	t_vector3d	speed;
	t_vector3d	pos3d;
	t_vector3d	collision_pos;
	t_vector3d	direction;
	float		direction_adjust;
	t_vector3d	current_tile;
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
	t_img	wall;
	t_img	ground;
	t_img	roof;
	// void	*wall;
	int		text_heigth;
	int		text_width;
}				t_texture;

typedef struct s_camera
{
	float	proj_plane_distance;
	float	proj_plane_height;
	float	proj_plane_width;
}					t_camera;

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
	t_player	player;
	t_texture	texture;
	t_camera	camera;
}				t_game;

// Ray casting
t_collision	cast_2D_ray(t_game *game, t_vector3d direction);

// Render
void	img_pix_put(t_img *img, int x, int y, int color);
void	clean_map(t_game *game);
void    render_fps(t_game *game);
void	clear_img(t_img *img);
int		get_color(t_img *img, int x, int y);

// Shapes
void	draw_square(t_game *game, t_vector3d pos, int width, int color);
void	draw_filled_square(t_game *game, t_vector3d pos, int width, int color);

void 	draw_circle(t_game *game, t_vector3d center, int radius, int color);
void	draw_filled_circle(t_img *img, t_vector3d mid, int radius, int color);

void	draw_vertical_line(t_game *game, t_vector3d pos, int len, int color);
void	draw_vertical_line_2(t_img *img, t_vector3d pos, int len, int color);
void	draw_non_filled_line(t_game *game, int x, int y, int len, int color);
void 	draw_line_dda(t_img *img, t_vector3d vec1, t_vector3d vec2, int color);

void	load_grid(t_game *game);
void	load_map(t_game *game);

// Events 
int		key_gestion(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_keypress(int keycode, t_game *game);
int 	game_loop(void *g);

t_vector3d pixel_to_tile(t_vector3d vector);
t_vector3d tile_to_pixel(t_vector3d tile_coord);
int tile_out_of_bound(t_vector3d tile_coord, t_game *game);
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

t_vector3d	vec_sum(t_vector3d vec1, t_vector3d vec2);
t_vector3d	vec_mult(t_vector3d vec1, t_vector3d vec2);
t_vector3d	vec_scalar_mult(t_vector3d vec1, double i);
t_vector3d	vec_normalize(t_vector3d vec);
t_vector3d	vec_rotate(t_vector3d vector, float angle);
void		vec_to_angle(double angle, t_vector3d *vector);
void		vec_print(t_vector3d *vector, char *name);
void		vec_rotate_rad(t_vector3d *vector, float angle);
void		vec_rotate_edit(t_vector3d *vector, float angle);
double		vec_distance(t_vector3d vec1, t_vector3d vec2);
double		vec_angle(t_vector3d v1, t_vector3d v2);
void		vec3_print(t_vector3d vector, char *name);
t_vector3d	vec_resize(t_vector3d vec1, double i);

#endif
