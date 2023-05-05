/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/05 12:23:03 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../cjson/cJSON.h"
# include "../includes/miniaudio.h"
# include "../libft/includes/libft.h"
# include "../mlx/mlx/mlx.h"
# include <dirent.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <time.h>

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

# define FOV_RADIANS (M_PI / 2)
# define FOV 60

# define RES_X 1600
# define RES_Y 900

// # define RES_X 300
// # define RES_Y 300

# define NB_THREADS 3

# define MOUSE_SENSITIVITY 1.5f

# ifndef HD
# 	define HD 1
# endif

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

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define BLACK_PIXEL 0x000000
# define GRAY_PIXEL 0xD9DADB
# define WHITE_PIXEL 0xFFFFFF
# define VIOLET 0x610627
# define DARK_VIOLET 0x2B0211
# define PALE_BLUE 0x25F7C6
# define PALE_BLUE_SHADED 0x0D5243

# include "structs.h"

// Color conversions
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				create_trgb(int t, int r, int g, int b);

// Color operations
int				add_shade(int trgb, int shade);
float			color_interpolate(int color1, int color2, double t);

// Ray casting
t_collision		cast_two_d_ray(t_game *game, t_vector3d direction);

int				sample_img(t_img *img, float x, float y);
void			fill_sprite_animation(t_game *game, char *dir_path,
					t_animation *animation);
void			sort_imgs(t_img **array);
void			ft_xpm_to_img(t_game *game, t_img *texture, char *path);
void			update_animation(t_game *game, t_animation *animation);
void			pre_compute_resize(t_game *game);
void			sample_img_to_img(t_img *dest, t_img *src, int start_x,
					int start_y);
int				divide_by_64(int value);

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
void			player_wall_collides(t_game *game, t_vector3d speed);
void			player_mobs_collide(t_game *game, t_sprite *sprites);
void			edit_player_pos(t_game *game);
void			edit_player_rotate(t_game *game);
void			update_player_tile_pos(t_player *player);
void			clear_z_buffer(t_game *game);
void			handle_weapon(t_game *game, t_weapon *weapon);
long			ft_now(void);
void			player_doors_open(t_game *game);
int				get_shotgun_distance(t_game *game);

// Events
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, int *key_states);
int				mouse_press(int button, int x, int y, t_game *game);
int				mouse_release(int button, int x, int y, t_game *game);
int				mouse_mouve_hook(int x, int y, t_game *game);

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
char			*img_get_addr(t_img *img, int x, int y);
void			render_fps(t_game *game);
void			render_map(t_game *game);
void			render(t_game *game);
void			render_ui(t_game *game);
void			clear_img(t_img *img);
int				get_color(t_img *img, int x, int y);
int				is_wall(char c);
void			get_wall(t_game *game, t_collision *collision, char c);
void			wall_render(t_game *game, t_collision collision,
					t_vector3d line_pos, double line_height);
void			render_sprites(t_game *game);
void			sort_sprites(t_sprite **headRef);
void			render_roof(t_game *game, t_vector3d v_ray_dir,
					t_vector3d line_pos, float line_height);
void			pre_compute_rows_dist(t_game *game, t_vector3d line_pos,
					float line_height, float resize);
void			precompute_raycast(t_game *game);
void			render_floor(t_game *game, t_vector3d v_ray_dir,
					t_vector3d line_pos);
void			render_floor_unicolor(t_game *game, t_vector3d line_pos);
void			render_roof_unicolor(t_game *game, t_vector3d line_pos, int line_height);
void			print_kill(t_game *game, int nb, int x);
void			print_fps(int fps);

int				handle_doors(t_game *game, t_raycast_data *d, int *tile_found);
char			get_collision_orientation(char last_step, t_vector3d v_step);
double			get_texture_x(char last_step, t_vector3d v_collision_point,
					t_vector3d v_map_check);

// Shapes
void			put_img_to_img(t_img *img, t_img *fill, int start_x,
					int start_y);
void			put_img_to_img_crop(t_img *img, t_img *fill, t_vector start,
					t_vector end);
void			put_img_to_img_alpha(t_img *img, t_img *fill, int start_x,
					int start_y);
void			put_img_to_img_green_alpha(t_img *img, t_img *fill, int start_x,
					int start_y);
void			put_img_to_img_faded(t_img *img, t_img *fill, int start_x, int start_y);

void			psychedelic_view(t_game *game, t_img *img);
void			red_view(t_game *game, t_img *img);
void			faded_view(t_game *game, t_img *img, int fading);
void			sample_map(t_img *dest, t_img *src, int start_x, int start_y);


// UI
void			handle_button(t_game *game, t_button *button);
void			render_menu(t_game *game);
void			menu_fade_out(t_game *game);

// Multithreading
void			wall_thread(t_game *game, t_wall_task d);
void			*start_thread(void *void_data);
void			submit_task_wall(t_game *game, t_wall_task task);

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
void			draw_filled_square(t_img *img, t_vector3d pos, int width,
					int color);
void			draw_circle(t_game *game, t_vector3d center, int radius,
					int color);
void			draw_filled_circle(t_img *img, t_vector3d mid, int radius,
					int color);
void			draw_vertical_line(t_img *img, t_vector3d pos, int len,
					int color);
void			draw_vertical_line_2(t_img *img, t_vector3d pos, int len,
					int color);
void			draw_line_dda(t_img *img, t_vector3d vec1, t_vector3d vec2,
					int color);
void			draw_filled_rectangle(t_img *img, t_vector3d vec,
					t_vector3d size, int color);
void			draw_square(t_img *img, t_vector3d pos, int width, int color);
void			load_grid(t_game *game);
void			load_map(t_game *game);

// Events
int				key_gestion(int keycode, t_game *game);
int				handle_keyrelease(int keycode, int *key_states);
int				handle_keypress(int keycode, t_game *game);
int				main_loop(void *g);


t_vector3d		get_next_tile(t_game *game, t_vector3d direction);
t_vector3d		pixel_to_tile(t_vector3d vector);
t_vector3d		tile_to_pixel(t_vector3d tile_coord);
int				pixel_out_of_bound(float x, float y, t_img *image);
char			**get_map(char *arg);
int				close_window(t_game *game);
void			move(t_game *game, char direction);

// mlx Utils
unsigned int	img_pix_read(t_img *img, int x, int y);

// INIT
void			var_init(t_game *game);
void			init_player(t_game *game);
void			init_weapons(t_game *game);
void			init_threads(t_game *game);
void			init_camera(t_game *game, t_camera *camera);
void			init_windows(t_game *game);
void			init_basic_vectors(t_game *game);
void			sound_state_init(t_sound_state *sound_state);

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
t_vector3d		vec_rotate_rad(t_vector3d vector, float angle);
void			vec_rotate_edit(t_vector3d *vector, float angle);
double			vec_distance(t_vector3d vec1, t_vector3d vec2);
double			vec3d_distance(t_vector3d vec1, t_vector3d vec2);
double			vec_angle(t_vector3d v1, t_vector3d v2);
t_vector3d		vec_copy(t_vector3d vec1);
t_vector3d		vec_zero(void);

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
void			init_sounds(t_audio *audio);
void			play_sound(ma_sound *sound);
void			game_sound(t_sound_state sound_state,
					ma_sound sound[NB_SOUNDS]);
void			restart_sound(ma_sound *sound);
void			add_sound(t_audio *audio, int id, char *path, float volume);
void			load_sounds(t_audio *audio);

/***********************************************************************************************
** $$$$$$\ $$\   $$\ $$\    $$\ $$$$$$$$\ $$\   $$\ $$$$$$$$\  $$$$$$\  $$$$$$$\ $$\     $$\  **
** \_$$  _|$$$\  $$ |$$ |   $$ |$$  _____|$$$\  $$ |\__$$  __|$$  __$$\ $$  __$$\\$$\   $$  | **
**   $$ |  $$$$\ $$ |$$ |   $$ |$$ |      $$$$\ $$ |   $$ |   $$/  $$ |$$ |  $$ |\$$\ $$  /  **
**   $$ |  $$ $$\$$ |\$$\  $$  |$$$$$\    $$ $$\$$ |   $$ |   $$ |  $$ |$$$$$$$  | \$$$$ /   **
**   $$ |  $$ \$$$$ | \$$\$$ / $$  __|   $$ \$$$$ |   $$ |   $$ |  $$ |$$  __$$<   \$$  /    **
**   $$ |  $$ |\$$$ |  \ $$$ /  $$ |      $$ |\$$$ |   $$ |   $$ |  $$ |$$ |  $$ |   $$ |     **
** $$$$$$\ $$ | \$$ |   \ $ /   $$$$$$$$\ $$ | \$$ |   $$ |    $$$$$$  |$$ |  $$ |   $$ |     **
** \______|\__|  \__|    \_/    \________|\__|  \__|   \__|    \______/ \__|  \__|   \__|     **
***********************************************************************************************/
void			entory(t_game *game);
void			refresh_inventory(t_game *game);
void			check_selected(t_game *game);
void			add_item(t_game *game, int id);
void			select_item(t_game *game, int x, int y);
int				get_item(int x, int y, int items[36]);
bool			item_out_of_bound(t_vector3d mouse, t_img img, t_img selected);
bool			is_consommable(t_sprite *item);
void			use_item(t_game *game, t_sprite *item);
void			inventory_switch(t_game *game);
bool			weapon_in_inventory(t_game *game, int id);
void			check_item(t_game *game);
void			swap_items(int first, int second, int items[36]);

/*********************************************************************************************
**  $$$$$$\  $$$$$$\ $$\   $$\  $$$$$$\  $$\       $$$$$$$$\ $$$$$$$$\  $$$$$$\  $$\   $$\  **
** $$  __$$\ \_$$  _|$$$\  $$ |$$  __$$\ $$ |      $$  _____|\__$$  __|$$  __$$\ $$$\  $$ | **
** $$ /  \__|  $$ |  $$$$\ $$ |$$ /  \__|$$ |      $$ |         $$ |   $$
	/  $$ |$$$$\ $$ | **
** \$$$$$$\    $$ |  $$ $$\$$ |$$ |$$$$\ $$ |      $$$$$\       $$ |   $$ |  $$ |$$ $$\$$ | **
**  \____$$\   $$ |  $$ \$$$$ |$$ |\_$$ |$$ |      $$  __|      $$ |   $$ |  $$ |$$ \$$$$ | **
** $$\   $$ |  $$ |  $$ |\$$$ |$$ |  $$ |$$ |      $$ |         $$ |   $$ |  $$ |$$ |\$$$ | **
** \$$$$$$  |$$$$$$\ $$ | \$$ |\$$$$$$  |$$$$$$$$\ $$$$$$$$\    $$ |    $$$$$$  |$$ | \$$ | **
**  \______/ \______|\__|  \__| \______/ \________|\________|   \__|    \______/ \__|  \__| **
*********************************************************************************************/
t_mlx			*_mlx(void);
t_garbage		*_gc(void);
t_garbage		*_gc_img(void);
t_garbage		*gc_new(void *content);
void			gc_add_back(t_garbage **gc, t_garbage *new);

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
t_sprite		*spawn_blood(t_game *game, t_vector3d pos, int type);
t_sprite		*sprite_last(t_sprite *lst);
void			sprite_add_back(t_sprite **lst, t_sprite *new);
void			sprite_add_front(t_sprite **lst, t_sprite *new);
void			load_zombie_anim(t_game *game);
void			load_blood_anim(t_game *game);
t_sprite		*spawn_item(t_game *game, t_vector3d pos, int id);
t_animation		load_item_anim(t_game *game, int id);
void			is_colliding(t_game *game, t_sprite *entity);
void			remove_entity(t_sprite **sprites, t_sprite *entity);
void			move_sprites(t_game *game, t_sprite **sprites,
					t_player *player);
bool			is_colliding_entity(t_sprite *sprites, t_sprite *entity);
bool			is_colliding_entity_dir(t_sprite *sprites, t_sprite *entity,
					char dir);
bool			can_attack(t_sprite *sprite, t_player *player);
void			update_width(t_sprite *sprite);
void			update_start_time(t_sprite *sprite, t_game *game);
void			attack(t_game *game, t_sprite *sprite, t_player *player);
bool			do_damage(int damage, t_sprite *sprite);
void			respawn_zombie(t_game *game);
void			set_baby_zombie_stats(t_sprite *zombie, t_wave *wave);
void			set_normal_zombie_stats(t_sprite *zombie, t_wave *wave);
void			set_big_zombie_stats(t_sprite *zombie, t_wave *wave);
void			set_type_specs_zomb(t_game *game, t_sprite *new_zombie,
					int type);
void	check_mob_collisions(t_sprite *sprite);
int		proj_mob_collide(t_sprite *mob, t_sprite *proj);
bool	projectile_terrain_collide(char **map, t_sprite *proj);
void	mob_wall_collide(t_game *game, t_sprite *mob);
void	mob_mob_collide(t_sprite *sprite_a, t_sprite *sprite_b);
void	sprite_spawn(t_game *game, t_sprite *sprite);
void	sprite_death(t_game *game, t_sprite *sprite);

//INIT
void			load_img(t_game *game);
t_img			create_img(char *path);
void			load_texture(t_game *game);
void			load_buttons(t_game *game);
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

// WAVES
t_wave			*get_wave(int wave_number);
void			check_wave(t_game *game);
void			update_kill(t_game *game);
void			spawn_wave(t_game *game);
void			fill_result(char *type, t_wave *result, int count,
					cJSON *zombies);
t_stats			get_stats(cJSON *zombies, const char *type);
void			auto_increase_difficulty(t_wave *wave, int wave_number);

#endif
