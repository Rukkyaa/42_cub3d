/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/12 17:53:53 by axlamber         ###   ########.fr       */
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
# include <dirent.h>

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

# define NB_THREADS 3

# define HD 1

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
# define GRAY_PIXEL  0xD9DADB
# define WHITE_PIXEL 0xFFFFFF
# define VIOLET_PIXEL 0x610627
# define DARK_VIOLET_PIXEL 0x2B0211
# define PALE_BLUE 	 0x25F7C6
# define PALE_BLUE_SHADED 	 0x0D5243

#include "structs.h"

// Color conversions
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
int					create_trgb(int t, int r, int g, int b);

// Color operations
int				add_shade(int trgb, int shade);

// Ray casting
t_collision		cast_2D_ray(t_game *game, t_vector3d direction);


int     sample_img(t_img *img, float x, float y);
void	fill_sprite_animation(t_game *game, char *dir_path, t_animation *animation);
void    sort_imgs(t_img **array);
void	ft_xpm_to_img(t_game *game, t_img *texture, char *path);
void    update_animation(t_game *game, t_animation *animation);
void 	pre_compute_resize(t_game *game);
void	sample_img_to_img(t_img *dest, t_img *src, int start_x, int start_y);
int 	divide_by_64(int value);

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
void			player_collides(t_game *game, t_vector3d speed);
void			edit_player_pos(t_game *game);
void			edit_player_rotate(t_game *game);
void			update_player_tile_pos(t_player	*player);
void			clear_z_buffer(t_game *game);
void    		handle_weapon(t_game *game, t_weapon *weapon);
long			ft_now(void);

//Fps
void			handle_sync(t_game *game);
void			handle_time(t_game *game);


/*****************************************************************
** $$$$$$$\  $$$$$$$$\ $$\   $$\ $$$$$$$\  $$$$$$$$\ $$$$$$$\   **
** $$  __$$\ $$  _____|$$$\ #include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> $$ |$$  __$$\ $$  _____|$$  __$$\  **
** $$ |  $$ |$$ |      $$$$\ $$ |$$ |  $$ |$$ |      $$ |  $$ | **
** $$$$$$$  |$$$$$\    $$ $$\$$ |$$ |  $$ |$$$$$\    $$$$$$$  | **
** $$  __$$< $$  __|   $$ \$$$$ |$$ |  $$ |$$  __|   $$  __$$<  **
** $$ |  $$ |$$ |      $$ |\$$$ |$$ |  $$ |$$ |      $$ |  $$ | **
** $$ |  $$ |$$$$$$$$\ $$ | \$$ |$$$$$$$  |$$$$$$$$\ $$ |  $$ | **
** \__|  \__|\________|\__|  \__|\_______/ \________|\__|  \__| **
*****************************************************************/
void			img_pix_put(t_img *img, int x, int y, int color);
char 			*img_get_addr(t_img *img, int x, int y);
void			render_fps(t_game *game);
void			render_map(t_game *game);
void			render(t_game *game);
void			render_ui(t_game *game);
void			clear_img(t_img *img);
int				get_color(t_img *img, int x, int y);
int				is_wall(char c);
void			get_wall(t_game *game, t_collision *collision, char c);
void 			wall_render(t_game *game, t_collision collision, t_vector3d line_pos, double line_height);
void    		render_sprites(t_game *game);
void 			sort_sprites(t_sprite** headRef);
void    		render_roof(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos, float line_height);
void    		pre_compute_rows_dist(t_game *game, t_vector3d line_pos, float line_height, float resize);
void    		render_floor(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos);
void			print_kill(t_game *game, int nb, int x);

// Shapes
void			draw_player(t_game *game, int color);
void			put_img_to_img(t_img *img, t_img *fill, int start_x, int start_y);
void			put_img_to_img_crop(t_img *img, t_img *fill, t_vector start, t_vector end);

void			psychedelic_view(t_game *game, t_img *img);


// Multithreading 
void    		wall_thread(t_game *game, t_wall_task d);
void    		*start_thread(void *void_data);
void    		submit_task_wall(t_game *game, t_wall_task task);

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
void			draw_filled_square(t_img *img, t_vector3d pos,
					int width, int color);
void			draw_circle(t_game *game, t_vector3d center,
					int radius, int color);
void			draw_filled_circle(t_img *img, t_vector3d mid,
					int radius, int color);
void			draw_vertical_line(t_img *img, t_vector3d pos, int len, int color);
void			draw_vertical_line_2(t_img *img, t_vector3d pos,
					int len, int color);
void			draw_line_dda(t_img *img, t_vector3d vec1,
					t_vector3d vec2, int color);
void			draw_filled_rectangle(t_img *img, t_vector3d vec,
					t_vector3d size, int color);
void			draw_square(t_img *img, t_vector3d pos, int width, int color);
void			load_grid(t_game *game);
void			load_map(t_game *game);

// Events 
int				key_gestion(int keycode, t_game *game);
int				handle_keyrelease(int keycode, int *key_states);
int				handle_keypress(int keycode, t_game *game);
int				game_loop(void *g);

// Controls
void	rotate_player(t_game *game, float angle);


t_vector3d		get_next_tile(t_game *game, t_vector3d direction);
t_vector3d		pixel_to_tile(t_vector3d vector);
t_vector3d		tile_to_pixel(t_vector3d tile_coord);
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

t_vector3d		vec_sum(t_vector3d vec1, t_vector3d vec2);
t_vector3d		vec_mult(t_vector3d vec1, t_vector3d vec2);
t_vector3d		vec_scalar_mult(t_vector3d vec1, double i);
t_vector3d		vec_normalize(t_vector3d vec);
t_vector3d		vec_rotate(t_vector3d vector, float angle);
void			vec_to_angle(double angle, t_vector3d *vector);
void			vec_print(t_vector3d *vector, char *name);
void			vec3_print(t_vector3d vector, char *name);
t_vector3d			vec_rotate_rad(t_vector3d vector, float angle);
void			vec_rotate_edit(t_vector3d *vector, float angle);
double			vec_distance(t_vector3d vec1, t_vector3d vec2);
double			vec3d_distance(t_vector3d vec1, t_vector3d vec2);
double			vec_angle(t_vector3d v1, t_vector3d v2);
t_vector3d		vec_copy(t_vector3d vec1);

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
void			add_item(t_game *game, char *type);
void			select_item(t_game *game, int x, int y);
char			*get_item(int x, int y, char *items[36]);
bool			item_out_of_bound(t_vector3d mouse, t_img img, t_img selected);
bool			is_consommable(t_sprite *item);
void			use_item(t_game *game, t_sprite *item);

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
t_garbage		*_gc(void);

/*************************************************************************
**  $$$$$$\  $$$$$$$\  $$$$$$$\  $$$$$$\ $$$$$$$$\ $$$$$$$$\  $$$$$$\   **
** $$  __$$\ $$  __$$\ $$  __$$\ \_$$  _|\__$$  __|$$  _____|$$  __$$\  **
** $$ /  \__|$$ |  $$ |$$ |  $$ |  $$ |     $$ |   $$ |      $$ /  \__| **
** \$$$$$$\  $$$$$$$  |$$$$$$$  |  $$ |     $$ |   $$$$$\    \$$$$$$\   **
**  \____$$\ $$  ____/ $$  __$$<   $$ |     $$ |   $$  __|    \____$$\  **
** $$\   $$ |$$ |      $$ |  $$ |  $$ |     $$ |   $$ |      $$\   $$ | **
** \$$$$$$  |$$ |      $$ |  $$ |$$$$$$\    $$ |   $$$$$$$$\ \$$$$$$  | **
**  \______/ \__|      \__|  \__|\______|   \__|   \________| \______/  **
*************************************************************************/
t_sprite		*spawn_zombie(t_game *game, t_vector3d pos, int type);
t_sprite		*spawn_projectile(t_game *game, t_vector3d pos, int type);
t_sprite		*sprite_last(t_sprite *lst);
void			sprite_add_back(t_sprite **lst, t_sprite *new);
void			load_zombie_anim(t_game *game);
t_sprite		*spawn_item(t_game *game, t_vector3d pos, char *type, int id);
t_animation		load_item_anim(t_game *game, char *type);
void			is_colliding(t_game *game, t_sprite *entity);
void			remove_entity(t_sprite **sprites, t_sprite *entity);
void			move_sprites(t_game *game, t_sprite **sprites, t_player *player);
bool			is_colliding_entity(t_sprite *sprites, t_sprite *entity);
bool			is_colliding_entity_dir(t_sprite *sprites, t_sprite *entity, char dir);
bool			can_attack(t_sprite *sprite, t_player *player);
void			update_width(t_sprite *sprite);
void			update_start_time(t_sprite *sprite, t_game *game);
void			attack(t_game *game, t_sprite *sprite, t_player *player);
bool			do_damage(int damage, t_sprite *sprite);


//INIT
void			load_img(t_game *game);
void			load_map_debug(t_game *game);

/***************************************************************************
**  $$$$$$\   $$$$$$\  $$$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$$\  **
** $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  _____| **
** $$ /  \__|$$ /  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$ /  \__|$$ |       **
** $$ |$$$$\ $$$$$$$$ |$$$$$$$  |$$$$$$$\ |$$$$$$$$ |$$ |$$$$\ $$$$$\     **
** $$ |\_$$ |$$  __$$ |$$  __$$< $$  __$$\ $$  __$$ |$$ |\_$$ |$$  __|    **
** $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |       **
** \$$$$$$  |$$ |  $$ |$$ |  $$ |$$$$$$$  |$$ |  $$ |\$$$$$$  |$$$$$$$$\  **
**  \______/ \__|  \__|\__|  \__|\_______/ \__|  \__| \______/ \________| **
***************************************************************************/
void			*my_alloc(int size);
void			free_garbage(void);
void			free_array(char **map);

#endif
