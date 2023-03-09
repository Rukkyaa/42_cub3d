/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 18:11:48 by teliet           ###   ########.fr       */
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
# include <float.h>
# include <time.h>
# include <sys/time.h>
# include <string.h>
# include "../includes/miniaudio.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define ESC 65307
# define A 97
# define W 119
# define D 100
# define S 115
# define E 101
# define RIGHT 65361
# define LEFT 65363
# define SHIFT 65505

# define FOV_RADIANS ( M_PI / 2 )
# define FOV 60

# define RES_X  1600
# define RES_Y  900
# define HALF_RES_X  800
# define HALF_RES_Y  450

# define MAX_DISTANCE 10

/****************************************************************
**  $$$$$$\   $$$$$$\  $$\       $$$$$$\  $$$$$$$\   $$$$$$\   **
** $$  __$$\ $$  __$$\ $$ |     $$  __$$\ $$  __$$\ $$  __$$\  **
** $$ /  \__|$$ /  $$ |$$ |     $$ /  $$ |$$ |  $$ |$$ /  \__| **
** $$ |      $$ |  $$ |$$ |     $$ |  $$ |$$$$$$$  |\$$$$$$\   **
** $$ |      $$ |  $$ |$$ |     $$ |  $$ |$$  __$$<  \____$$\  **
** $$ |  $$\ $$ |  $$ |$$ |     $$ |  $$ |$$ |  $$ |$$\   $$ | **
** \$$$$$$  | $$$$$$  |$$$$$$$$\ $$$$$$  |$$ |  $$ |\$$$$$$  | **
**  \______/  \______/ \________|\______/ \__|  \__| \______/  **
****************************************************************/

# define RED_PIXEL   0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL  0x0000FF
# define BLACK_PIXEL 0x000000
# define WHITE_PIXEL 0xFFFFFF
# define PALE_BLUE 	 0x25F7C6
# define PALE_BLUE_SHADED 	 0x0D5243


// Color conversions
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);

// Color operations
int					add_shade(int trgb, int shade);
/***************************************************************
**  $$$$$$\ $$$$$$$$\ $$$$$$$\  $$\   $$\  $$$$$$\ $$$$$$$$\  **
** $$  __$$\\__$$  __|$$  __$$\ $$ |  $$ |$$  __$$\\__$$  __| **
** $$ /  \__|  $$ |   $$ |  $$ |$$ |  $$ |$$ /  \__|  $$ |    **
** \$$$$$$\    $$ |   $$$$$$$  |$$ |  $$ |$$ |        $$ |    **
**  \____$$\   $$ |   $$  __$$  $$ |  $$ |$$ |        $$ |    **
** $$\   $$ |  $$ |   $$ |  $$ |$$ |  $$ |$$ |  $$\   $$ |    **
** \$$$$$$  |  $$ |   $$ |  $$ |\$$$$$$  |\$$$$$$  |  $$ |    **
**  \______/   \__|   \__|  \__| \______/  \______/   \__|    **
***************************************************************/

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

typedef struct s_time
{
	struct timeval	last_frame;
	struct timeval	frame;
	long			delta_frame_ms;
	int				fps;
}					t_time;

typedef struct s_camera
{
	float	proj_plane_distance;
	float	proj_plane_height;
	float	proj_plane_width;
	t_vector			plane;
}					t_camera;

typedef struct s_player
{
	t_vector	pos;
	t_vector	speed;
	t_vector3d	pos3d;
	t_vector	collision_pos;
	t_vector	direction;
	float		angle;
	float		direction_adjust;
	t_vector	current_tile;
}				t_player;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
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

typedef struct s_sprite
{
	int		type;
	int 	state;
	float	height;
	float	width;
	float	distance;
	float	screen_width;
	float	screen_height;
	int		visible;
	t_vector	screen_pos;
	t_img	texture;
	t_vector3d	pos;
}				t_sprite;


typedef struct s_collision
{
	t_vector		point;
	t_img			wall;
	char			orientation;
	float			distance;
	float			x_pos_tex;
}					t_collision;

typedef struct s_weapon
{
	t_img	sword;
}				t_weapon;

typedef struct s_inventory
{
	t_img	img;
	char	*items[36];
}				t_inventory;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		img;
}				t_mlx;

typedef struct s_game
{
	void 		*mlx;
	int			time_inc;
	char		**map;
	int			key_states[256];
	int			key_release_states[256];
	t_inventory	inventory;
	t_weapon	weapon;
	t_time		time;
	t_vector	mouse;
	t_player	player;
	t_sprite	sprites[10];
	float			z_buffer[RES_X];
	float			ray_offset[RES_X];
	t_texture	texture;
	t_sounds	sounds;
	t_camera	camera;
	t_vector	v_up;
	t_vector	v_down;
	t_vector	v_left;
	t_vector	v_right;
	void		*fps_win;
	t_img		fps_img;
	void		*debug_win;
	t_img		debug_img;
}				t_game;

// Ray casting
t_collision		cast_2D_ray(t_game *game, t_vector direction);

/************************************************
**  $$$$$$\   $$$$$$\  $$\      $$\ $$$$$$$$\  **
** $$  __$$\ $$  __$$\ $$$\    $$$ |$$  _____| **
** $$ /  \__|$$ /  $$ |$$$$\  $$$$ |$$ |       **
** $$ |$$$$\ $$$$$$$$ |$$\$$\$$ $$ |$$$$$\     **
** $$ |\_$$ |$$  __$$ |$$ \$$$  $$ |$$  __|    **
** $$ |  $$ |$$ |  $$ |$$ |\$  /$$ |$$ |       **
** \$$$$$$  |$$ |  $$ |$$ | \_/ $$ |$$$$$$$$\  **
**  \______/ \__|  \__|\__|     \__|\________| **
************************************************/
//Move
void			hooks(t_game *game);
bool			is_key(int keycode);
bool			is_walkable(t_game *game, int x, int y);
bool			is_collectible(t_game *game);

bool			player_moving(t_game *game);
void			player_collides(t_game *game, t_vector speed);
void			edit_player_pos(t_game *game);
void			edit_player_rotate(t_game *game);

//Fps
void			handle_sync(t_game *game);
void			handle_time(t_game *game);


/*****************************************************************
** $$$$$$$\  $$$$$$$$\ $$\   $$\ $$$$$$$\  $$$$$$$$\ $$$$$$$\   **
** $$  __$$\ $$  _____|$$$\  $$ |$$  __$$\ $$  _____|$$  __$$\  **
** $$ |  $$ |$$ |      $$$$\ $$ |$$ |  $$ |$$ |      $$ |  $$ | **
** $$$$$$$  |$$$$$\    $$ $$\$$ |$$ |  $$ |$$$$$\    $$$$$$$  | **
** $$  __$$< $$  __|   $$ \$$$$ |$$ |  $$ |$$  __|   $$  __$$<  **
** $$ |  $$ |$$ |      $$ |\$$$ |$$ |  $$ |$$ |      $$ |  $$ | **
** $$ |  $$ |$$$$$$$$\ $$ | \$$ |$$$$$$$  |$$$$$$$$\ $$ |  $$ | **
** \__|  \__|\________|\__|  \__|\_______/ \________|\__|  \__| **
*****************************************************************/
void			img_pix_put(t_img *img, int x, int y, int color);
void			render_fps(t_game *game);
void			render_map(t_game *game);
void			render(t_game *game);
void			render_ui(t_game *game);
void			clear_img(t_img *img);
int				get_color(t_img *img, int x, int y);
int				is_wall(char c);
void			get_wall(t_game *game, t_collision *collision, char c);
void 			wall_render(t_game *game, t_collision collision, t_vector line_pos, double line_height);
void    		render_sprites(t_game *game);
void 			sort_sprites(t_sprite sprites[], int size);

// Shapes
void			draw_player(t_game *game, int color);
void			put_img_to_img(t_img img, t_img fill, int start_x, int start_y);
void			psychedelic_view(t_game *game, t_img *img);


/*****************************************************************
**  $$$$$$\  $$\   $$\  $$$$$$\  $$$$$$$\  $$$$$$$$\  $$$$$$\   **
** $$  __$$\ $$ |  $$ |$$  __$$\ $$  __$$\ $$  _____|$$  __$$\  **
** $$ /  \__|$$ |  $$ |$$ /  $$ |$$ |  $$ |$$ |      $$ /  \__| **
** \$$$$$$\  $$$$$$$$ |$$$$$$$$ |$$$$$$$  |$$$$$\    \$$$$$$\   **
**  \____$$\ $$  __$$ |$$  __$$ |$$  ____/ $$  __|    \____$$\  **
** $$\   $$ |$$ |  $$ |$$ |  $$ |$$ |      $$ |      $$\   $$ | **
** \$$$$$$  |$$ |  $$ |$$ |  $$ |$$ |      $$$$$$$$\ \$$$$$$  | **
**  \______/ \__|  \__|\__|  \__|\__|      \________| \______/  **
*****************************************************************/
void			draw_filled_square(t_img *img, t_vector pos,
					int width, int color);
void			draw_circle(t_game *game, t_vector center,
					int radius, int color);
void			draw_filled_circle(t_img *img, t_vector mid,
					int radius, int color);
void			draw_vertical_line(t_img *img, t_vector pos, int len, int color);
void			draw_vertical_line_2(t_img *img, t_vector pos,
					int len, int color);
void			draw_line_dda(t_img *img, t_vector vec1,
					t_vector vec2, int color);
void			draw_filled_rectangle(t_img *img, t_vector vec,
					t_vector size, int color);
void			load_grid(t_game *game);
void			load_map(t_game *game);

// Events 
int				key_gestion(int keycode, t_game *game);
int				handle_keyrelease(int keycode, int *key_states);
int				handle_keypress(int keycode, t_game *game);
int				game_loop(void *g);

// Controls
void	rotate_player(t_game *game, float angle);


t_vector		get_next_tile(t_game *game, t_vector direction);
t_vector		pixel_to_tile(t_vector vector);
t_vector		tile_to_pixel(t_vector tile_coord);
int				pixel_out_of_bound(float x, float y, t_img *image);
void			var_init(t_game *game);
char			**get_map(char *arg);
int				close_window(t_game *game);
void			move(t_game *game, char direction);

// mlx Utils
unsigned int	img_pix_read(t_img *img, int x, int y);

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

int				map_heigth(char **map);
int				map_width(char **map);
char			**get_map(char *arg);

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

t_vector		vec_sum(t_vector vec1, t_vector vec2);
t_vector		vec_mult(t_vector vec1, t_vector vec2);
t_vector		vec_scalar_mult(t_vector vec1, double i);
t_vector		vec_normalize(t_vector vec);
t_vector		vec_rotate(t_vector vector, float angle);
void			vec_to_angle(double angle, t_vector *vector);
void			vec_print(t_vector *vector, char *name);
void			vec_rotate_rad(t_vector *vector, float angle);
void			vec_rotate_edit(t_vector *vector, float angle);
double			vec_distance(t_vector vec1, t_vector vec2);
double			vec3d_distance(t_vector3d vec1, t_vector3d vec2);
double			vec_angle(t_vector v1, t_vector v2);
t_vector		vec_copy(t_vector vec1);

/*******************************************************
**  $$$$$$\   $$$$$$\  $$\   $$\ $$\   $$\ $$$$$$$\   **
** $$  __$$\ $$  __$$\ $$ |  $$ |$$$\  $$ |$$  __$$\  **
** $$ /  \__|$$ /  $$ |$$ |  $$ |$$$$\ $$ |$$ |  $$ | **
** \$$$$$$\  $$ |  $$ |$$ |  $$ |$$ $$\$$ |$$ |  $$ | **
**  \____$$\ $$ |  $$ |$$ |  $$ |$$ \$$$$ |$$ |  $$ | **
** $$\   $$ |$$ |  $$ |$$ |  $$ |$$ |\$$$ |$$ |  $$ | **
** \$$$$$$  | $$$$$$  |\$$$$$$  |$$ | \$$ |$$$$$$$  | **
**  \______/  \______/  \______/ \__|  \__|\_______/  **
*******************************************************/
void			load_sounds(t_sounds *sounds);
void			clear_sounds(t_sounds *sounds);

/***********************************************************************************************
** $$$$$$\ $$\   $$\ $$\    $$\ $$$$$$$$\ $$\   $$\ $$$$$$$$\  $$$$$$\  $$$$$$$\ $$\     $$\  **
** \_$$  _|$$$\  $$ |$$ |   $$ |$$  _____|$$$\  $$ |\__$$  __|$$  __$$\ $$  __$$\\$$\   $$  | **
**   $$ |  $$$$\ $$ |$$ |   $$ |$$ |      $$$$\ $$ |   $$ |   $$ /  $$ |$$ |  $$ |\$$\ $$  /  **
**   $$ |  $$ $$\$$ |\$$\  $$  |$$$$$\    $$ $$\$$ |   $$ |   $$ |  $$ |$$$$$$$  | \$$$$  /   **
**   $$ |  $$ \$$$$ | \$$\$$  / $$  __|   $$ \$$$$ |   $$ |   $$ |  $$ |$$  __$$<   \$$  /    **
**   $$ |  $$ |\$$$ |  \$$$  /  $$ |      $$ |\$$$ |   $$ |   $$ |  $$ |$$ |  $$ |   $$ |     **
** $$$$$$\ $$ | \$$ |   \$  /   $$$$$$$$\ $$ | \$$ |   $$ |    $$$$$$  |$$ |  $$ |   $$ |     **
** \______|\__|  \__|    \_/    \________|\__|  \__|   \__|    \______/ \__|  \__|   \__|     **
***********************************************************************************************/
void			init_inventory(t_game *game);
void			refresh_inventory(t_game *game);
void			add_item(t_game *game, char *str);

/*********************************************************************************************
**  $$$$$$\  $$$$$$\ $$\   $$\  $$$$$$\  $$\       $$$$$$$$\ $$$$$$$$\  $$$$$$\  $$\   $$\  **
** $$  __$$\ \_$$  _|$$$\  $$ |$$  __$$\ $$ |      $$  _____|\__$$  __|$$  __$$\ $$$\  $$ | **
** $$ /  \__|  $$ |  $$$$\ $$ |$$ /  \__|$$ |      $$ |         $$ |   $$ /  $$ |$$$$\ $$ | **
** \$$$$$$\    $$ |  $$ $$\$$ |$$ |$$$$\ $$ |      $$$$$\       $$ |   $$ |  $$ |$$ $$\$$ | **
**  \____$$\   $$ |  $$ \$$$$ |$$ |\_$$ |$$ |      $$  __|      $$ |   $$ |  $$ |$$ \$$$$ | **
** $$\   $$ |  $$ |  $$ |\$$$ |$$ |  $$ |$$ |      $$ |         $$ |   $$ |  $$ |$$ |\$$$ | **
** \$$$$$$  |$$$$$$\ $$ | \$$ |\$$$$$$  |$$$$$$$$\ $$$$$$$$\    $$ |    $$$$$$  |$$ | \$$ | **
**  \______/ \______|\__|  \__| \______/ \________|\________|   \__|    \______/ \__|  \__| **
*********************************************************************************************/
t_mlx			*_mlx(void);

#endif
