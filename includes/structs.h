/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:45:58 by theo              #+#    #+#             */
/*   Updated: 2023/04/13 17:00:06 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define MOB 0
# define ITEM 1
# define PROJ 2

# define IDLE 0
# define FIRE 1
# define RELOAD 2

# define RUN 0
# define ATTACK 1
# define DEATH 2
# define SPAWN 3

// Projectiles
# define GREEN_PROJ 0
# define BLUE_PROJ 1

// Items
# define AXE 1
# define PLASMA_RIFFLE 2
# define HEALTH 50
# define COCAINE 51

// Zombies
# define NORMAL_ZOMBIE 0
# define BIG_ZOMBIE 1
# define BABY_ZOMBIE 2

# define MAP_MARGIN 160

typedef int WEAPON;

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

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}				t_garbage;

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
	t_vector3d			half_res;
	t_vector3d			plane;
	t_vector3d			plane_center;
}					t_camera;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		heigth;
    char    *name;
}	t_img;

// TEXTURE
typedef struct s_texture
{
	t_img	wall1;
	t_img	wall2;
	t_img	wall3;
	t_img	wall4;
	t_img	door;
	t_img	ground;
	t_img	roof;
	t_img	projectile;
	t_img	blue_projectile;
	t_img	heart;
	t_img	cocaine;
	t_img	number[10];
	int		text_heigth;
	int		text_width;
}				t_texture;

// ---------------- SPRITES --------------

typedef struct s_animation
{
	t_img	**imgs;
	t_img	*current_img;
	int		frame_duration_ms;
	int		nb_imgs;
	int		current_frame;
	int		frame_offset;
	long	start_time_ms;
}				t_animation;

typedef struct s_animations
{
	t_animation	zombie_run;
	t_animation	zombie_walk;
	t_animation	zombie_hit;
	t_animation	zombie_death;
	t_animation	zombie_spawn;
	t_animation	axe;
	t_animation	plasma_riffle;
	t_animation	heart;
	t_animation	cocaine;
}				t_animations;

typedef struct s_animated_mob
{
	t_animation spawn;
	t_animation run;
	t_animation hit;
	t_animation death;
}				t_animated_mob;

typedef struct s_sprite
{
	int				type;
	int				visible;
	int				hp;
	int				state;
	int				id;
	int				damage;
	float			height;
	float			width;
	float			distance;
	float			angle_to_player;
	float			screen_width;
	float			screen_height;
	float			velocity;
	bool			attacked;
	int				collide_width;
	t_vector3d		screen_pos;
	t_animation		animation;
	t_img			*current_img;
	t_img			**img_run;
	t_vector3d		last_pos;
	t_vector3d		pos;
	t_vector3d		speed;
	t_animated_mob	animated_mob;
	struct s_sprite	*next;
}				t_sprite;


// ---------------------------------------

typedef struct s_weapon_icons
{
	t_img		sword;
	t_img		axe;
	t_img		plasma_riffle;
}				t_weapon_icons;

typedef struct s_weapon
{
	int			state;
	t_img		*idle_img;
	t_img		*current_img;
	t_animation fire_anim;
	int			is_melee;
	int			projectile;
	float		auto_attack;
	float		cool_down_ms;
	float		attack_speed;
	float		damage;
	float		ammo;
	long		last_attack;
	t_vector	screen_pos;
}				t_weapon;

typedef struct s_weapons
{
	t_weapon		axe;
	t_weapon		grap_gun;
	t_weapon		plasma_riffle;
}				t_weapons;

typedef struct s_player
{
	t_vector3d	pos;
	t_vector3d	speed;
	t_vector3d	pos3d;
	t_vector3d	tile_pos;
	t_vector3d	collision_pos;
	t_vector3d	direction;
	t_weapon	*weapon;
	int			weapon_selected;
	int			kills;
	int 		tilt;
	int			max_hp;
	int			hp;
	int			velocity;
	float		angle;
	float		direction_adjust;
	int			bonus_strength;
	long		start_cocaine;
	bool		cocaine;
	t_vector3d	current_tile;
}				t_player;

typedef struct s_collision
{
	t_vector3d		point;
	t_img			wall;
	char			orientation;
	float			distance;
	float			x_pos_tex;
}					t_collision;

typedef struct s_inventory
{
	t_img	img;
	t_img	*selected_img;
	int		selected;
	WEAPON	items[36];
}				t_inventory;

typedef struct s_hud
{
	t_img		life_red_bar;
	t_img		life_orange_bar;
	t_img		life_green_bar;
	t_img		life_bar_border;
	t_img		aim;
	t_img		weapon;
	t_animation	weapon_anim;
}				t_hud;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		img;
}				t_mlx;


// ---------------- MULTI-THREADING --------------

typedef struct s_wall_task
{
	t_collision		collision;
	t_vector3d		v_ray_dir;
	t_vector3d		line_pos;
	int				line_height;
}				t_wall_task;


// -----------------------------------------------

typedef struct s_game
{
	void 			*mlx;
	int				frame_count;
	char			**map;
	int				key_states[256];
	int				key_release_states[256];
	t_inventory		inventory;
	t_hud			hud;
	t_weapon_icons	weapon_icons;
	t_weapons		weapons;
	t_time			time;
	t_vector3d		mouse;
	t_vector3d		mouse_diff;
	t_animations	animations;
	int				mouse_move;
	t_player		player;
	t_sprite		*sprites;
	float			z_buffer[RES_X];
	float			row_dist[RES_X][RES_Y];
	float			ray_offset[RES_X];
	float			ray_angle[RES_X];
	float			fisheye_resize[RES_X];
	float			fisheye_resize_wall[RES_X];
	int				wall_height;
	int				wall_height_x_proj_dist;
	t_texture		texture;
	t_sounds		sounds;
	t_camera		camera;
	t_vector3d		v_up;
	t_vector3d		v_down;
	t_vector3d		v_left;
	t_vector3d		v_right;
	t_vector3d		minimap_center;
	void			*fps_win;
	t_img			fps_img;
	void			*debug_win;
	t_img			debug_img;
	t_img			minimap;
	int				mouse_clicked;
	int				inventory_display;

	pthread_t 		wall_threads[NB_THREADS];
	t_wall_task 	wall_tasks[RES_X];
	pthread_mutex_t	print_rights;
	pthread_mutex_t	img_read_rights;
	pthread_mutex_t	img_put_rights;
	pthread_mutex_t	render_finished_rights;
	pthread_mutex_t	queue_rights;
	int				task_count;
	int				task_done;
	int				render_finished;
}				t_game;


#endif
