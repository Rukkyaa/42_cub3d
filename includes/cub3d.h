/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/09 11:35:56 by teliet           ###   ########.fr       */
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
# include <string.h>
# include <stdbool.h>

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


# define FOV_RADIANS ( M_PI / 2 )
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

# define PARSING_ERROR 0
# define MLX_CREATION_ERROR 1
# define INIT_MALLOC_ERROR 2
# define XPM_ERROR 3
# define ADDR_ERROR 4
# define INIT_ERROR 5
# define MALLOC_ERROR 6

// TEXTURE

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
	t_vector	collision_pos;
	t_vector	direction;
	t_vector	speed;
	float			direction_adjust;
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
	t_img	wall;
	int		text_heigth;
	int		text_width;
	int		floor_color;
	int		sky_color;
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
}				t_texture;

typedef struct s_parsing
{
	char		**map;
	t_vector	player_pos;
	int			floor_color[3];
	int			ceiling_color[3];
	int			map_width;
	int			map_height;
	char		player_dir;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_parsing;

typedef struct s_raycast_data
{
	struct vector v_ray_dir;
	struct vector v_step;
	struct vector v_ray_length_1D;
	struct vector v_map_check;
	struct vector v_ray_unit_step;
    struct vector collision_point;
    t_collision collision;
    float distance;
	char		last_step;
}				t_raycast_data;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}				t_garbage;

typedef struct s_game
{
	void		*mlx;
	void		*fps_win;
	t_img		fps_img;
	char		**map;
	int				key_states[256];
	int				key_release_states[256];
	t_player	player;
	t_texture	texture;
	t_parsing	*parsing;
}				t_game;

t_game		*_game(void);
t_garbage	*_gc(void);
t_garbage	*_gc_img(void);
void		free_garbage(int exit_code);
void		*my_alloc(int size);
void		free_array(char **map);
t_garbage	*gc_new(void *content);
void		gc_add_back(t_garbage **gc, t_garbage *new);

int			map_height(char **map);
int			map_width(char **map);
char		**get_map_parse(int fd);
t_parsing	*parse(char	*map_path);
void		free_map(char **map);
char		**map_dup(char **map);
bool		is_map_valid(t_parsing *parsing);
int			ft_atoi(const char *str);
int			len_num(const char *line);

bool		get_params(t_parsing *parsing, int fd);
bool		get_map_color(t_parsing *parsing, char *line);
bool		is_texture(char *line);
bool		fill_texture(t_parsing *parsing, char *line);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// GNL
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*get_next_line(int fd);

// Ray casting
t_collision	cast_two_d_ray(t_game *game, t_vector direction);
char		get_collision_orientation(char last_step, t_vector v_step);
double		get_texture_x(char last_step, t_vector v_collision_point,
	t_vector v_map_check);
void	get_wall(t_game *game, t_collision *collision, char c);

// Render
void	img_pix_put(t_img *img, int x, int y, int color);
void	clean_map(t_game *game);
void    render_fps(t_game *game);
void	render(t_game *game);
void	clear_img(t_img *img);
int		get_color(t_img *img, int x, int y);

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

t_vector pixel_to_tile(t_vector vector);
t_vector tile_to_pixel(t_vector tile_coord);
int tile_out_of_bound(t_vector tile_coord, t_game *game);
int pixel_out_of_bound(float x, float y, t_img *image);
void	draw_player(t_game *game, int color);
void	var_init(void);
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
// char	**get_map(char *arg);

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
double		vec_angle(t_vector v1, t_vector v2);

#endif
