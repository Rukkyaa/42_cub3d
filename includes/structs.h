/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:45:58 by theo              #+#    #+#             */
/*   Updated: 2023/03/22 14:02:02 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_player
{
	t_vector3d	pos;
	t_vector3d	speed;
	t_vector3d	pos3d;
	t_vector3d	tile_pos;
	t_vector3d	collision_pos;
	t_vector3d	direction;
	int 		tilt;
	float		angle;
	float		direction_adjust;
	t_vector3d	current_tile;
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
    char    *name;
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
	t_img	projectile;
	int		text_heigth;
	int		text_width;
}				t_texture;

// ---------------- SPRITES --------------

typedef struct s_animation
{
	t_img		 **imgs;
	t_img		 *current_img;
	int          frame_duration_ms;
	int          nb_imgs;
	int          frame_offset;
	long		start_time_ms;
}				t_animation;

typedef struct s_animated_mob
{
	t_animation idle;
	t_animation walk;
	t_animation run;
}				t_animated_mob;

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
	t_vector3d	screen_pos;
	t_animation	animation;
	t_img	*current_img;
	t_img	**img_run;
	t_vector3d	pos;
}				t_sprite;


// ---------------------------------------

typedef struct s_collision
{
	t_vector3d		point;
	t_img			wall;
	char			orientation;
	float			distance;
	float			x_pos_tex;
}					t_collision;

typedef struct s_weapon
{
	t_img	sword;
	t_img	axe;
}				t_weapon;

typedef struct s_inventory
{
	t_img	img;
	t_img	*selected_img;
	int		selected;
	char	*items[36];
}				t_inventory;

typedef struct s_hud
{
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

typedef struct s_game
{
	void 		*mlx;
	int			frame_count;
	char		**map;
	int			key_states[256];
	int			key_release_states[256];
	t_inventory	inventory;
	t_hud		hud;
	t_weapon	weapon;
	t_time		time;
	t_vector3d	mouse;
	t_vector3d	mouse_diff;
	float		mouse_move;
	t_player	player;
	t_sprite	sprites[11];
	float			z_buffer[RES_X];
	float			row_dist[RES_Y];
	float			ray_offset[RES_X];
	float			ray_angle[RES_X];
	float			fisheye_resize[RES_X];
	float			fisheye_resize_wall[RES_X];
	int			wall_height;
	int			wall_height_x_proj_dist;
	t_texture	texture;
	t_sounds	sounds;
	t_camera	camera;
	t_vector3d	v_up;
	t_vector3d	v_down;
	t_vector3d	v_left;
	t_vector3d	v_right;
	t_vector3d	minimap_center;
	void		*fps_win;
	t_img		fps_img;
	void		*debug_win;
	t_img		debug_img;
	t_img		minimap;
}				t_game;
