/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/02 19:34:41 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_animations(t_game *game)
{
	game->animations.zombie_run = get_zombie_anim(game);
	game->animations.sword = get_item_anim(game);
}

void	init_camera(t_camera *camera)
{
	camera->proj_plane_height =  RES_Y;
	camera->proj_plane_width =  RES_X ; //camera->proj_plane_height * ( (float) RES_X / (float) RES_Y);
	camera->half_res.x = RES_X / 2;
	camera->half_res.y = RES_Y / 2;
	camera->proj_plane_distance = ((float) camera->proj_plane_width / 2.0f) / tanf(FOV_RADIANS / 2.0f);
	//camera->proj_plane_distance = 277;
	camera->plane.x = 0;
	camera->plane.y = camera->proj_plane_width / 2;
	camera->plane_center.x = camera->half_res.x;
	camera->plane_center.y = camera->half_res.y;
	
}

void	init_basic_vectors(t_game *game)
{
	game->v_left.x = -1;
	game->v_left.y = 0;
	game->v_right.x = 1;
	game->v_right.y = 0;
	game->v_up.x = 0;
	game->v_up.y = -1;
	game->v_down.x = 0;
	game->v_down.y = 1;
}

void init_sprites(t_game *game)
{
	int i = 0;
	t_sprite	*tmp;
	t_vector zombie_pos;

	init_animations(game);
	game->sprites = NULL;
	while(i < 10)
	{
		zombie_pos.x = (double)rand() / (double)RAND_MAX * map_width(game->map) * 64;
		zombie_pos.y = (double)rand() / (double)RAND_MAX * map_width(game->map) * 64;
		
		tmp = spawn_zombie(game, zombie_pos);
		if (!tmp)
			printf("error spawn zombie\n");
		i++;
	}
	t_vector item_pos;
	item_pos.x = 3.0 * 64;
	item_pos.y = 3.0 * 64;
	tmp = spawn_item(game, item_pos);
	if (!tmp)
		printf("error spawn zombie\n");
}

void init_weapons(t_game *game)
{
	t_animation grap_gun;
	grap_gun.imgs = fill_sprite_animation(game, "images/weapons/Grap_gun_upscale_xpm_alpha_resized_fuzz");
	grap_gun.current_img = grap_gun.imgs[0];
	// printf("anim\n");
	grap_gun.frame_duration_ms = 100;
	grap_gun.frame_offset = 0;
	grap_gun.nb_imgs = 16;
	grap_gun.start_time_ms = game->time.frame.tv_sec * 1000 + game->time.frame.tv_usec / 1000;
	game->hud.weapon_anim = grap_gun;
}


void	precompute_raycast(t_game *game)
{
	int	i = 0;
    t_vector3d v_ray_dir;
    t_vector3d v_right;
    t_vector3d v_player_to_camera_plane;
	
    v_right  = vec_normalize(game->camera.plane) ;
	v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
	while(i < RES_X)
	{
        game->ray_offset[i] = ((2.0f * (float) i / (RES_X - 1.0f)) - 1.0f) * (game->camera.proj_plane_width / 2);
		
		v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[i]));
        v_ray_dir = vec_normalize(v_ray_dir);
        game->ray_angle[i] =  vec_angle(game->player.direction, v_ray_dir);
		i++;
	}
}

void	init_mutex(t_game *game, pthread_mutex_t *mutex)
{
		if (pthread_mutex_init(mutex, NULL) != 0)
		{
			printf("pthread_mutex_init error");
			close_window(game);
		}	
}

void	init_threads(t_game *game)
{
	int i;

	i = 0;
	while(i < NB_THREADS)
	{
		pthread_create(&game->wall_threads[i], NULL, start_thread, (void*) game);
		i++;
	}	
	init_mutex(game, &game->print_rights);
	init_mutex(game, &game->img_read_rights);
	init_mutex(game, &game->img_put_rights);
	init_mutex(game, &game->queue_rights);
	init_mutex(game, &game->render_finished_rights);
	game->render_finished = 0;
	game->task_count = 0;
	game->task_done = 0;
}


void	var_init(t_game *game)
{
	int i = 256;
	while(i--)
		game->key_states[i] = 0;
	i = 256;
	while(i--)
		game->key_release_states[i] = 1;
	game->mlx = _mlx()->mlx;
	// game->debug_win = mlx_new_window( _mlx()->mlx, map_width(game->map) * 64, map_heigth(game->map) * 64, "map");
	game->player.pos.x = 20*64 + 32;
	game->player.pos.y = 5*64 + 32;
	game->player.collision_pos.x = game->player.pos.x + 32;
	game->player.collision_pos.y = game->player.pos.y + 32;
	game->player.pos3d.x = 30*64 + 32;
	game->player.pos3d.y = 30*64 + 32; 
	game->player.pos3d.z = 32;
	game->player.direction.x = 1;
	game->player.direction.y = 0; 
	game->player.direction.z = 0; 
	game->player.tilt = 0; 
	game->player.angle = 0; 
	game->player.speed.x = 0;
	game->player.speed.y = 0; 
	game->player.direction_adjust = 10; 
	game->frame_count = 0;
	game->time.delta_frame_ms = 0;
	game->time.fps = 0;
	game->wall_height = 64;
	game->mouse_move = 0;
	// angle_to_vector( M_PI / 4, &game->player.direction);
    // vec_print(&game->player.direction, "player dir");
	// close_window(game);
	game->debug_img.mlx_img = mlx_new_image(game->mlx, map_width(game->map) * 64, map_heigth(game->map) * 64);
	game->debug_img.addr = mlx_get_data_addr(game->debug_img.mlx_img, &game->debug_img.bpp,
			&game->debug_img.line_len, &game->debug_img.endian);
	game->minimap.mlx_img = mlx_new_image(game->mlx, 224, 224);
	game->minimap.addr = mlx_get_data_addr(game->minimap.mlx_img, &game->minimap.bpp,
			&game->minimap.line_len, &game->minimap.endian);
	game->minimap.width = 224;
	game->minimap.heigth = 224;
	game->minimap_center.x = game->minimap.width / 2;
	game->minimap_center.y =  game->minimap.heigth / 2;
	game->debug_img.width =  map_width(game->map) * 64;
	game->debug_img.heigth = map_heigth(game->map) * 64;
	game->fps_win = _mlx()->win;
	game->fps_img = _mlx()->img;
	game->mouse_clicked  = 0;
	init_camera(&game->camera);
	game->wall_height_x_proj_dist = game->wall_height * game->camera.proj_plane_distance;
	game->mouse.x = RES_X / 2;
	game->mouse.y = RES_Y / 2;
	precompute_raycast(game);
	pre_compute_resize(game);
	load_img(game);
	load_map(game);
	// load_sounds(&game->sounds);
	init_basic_vectors(game);
	init_inventory(game);
	mlx_put_image_to_window(game->mlx, _mlx()->win, _mlx()->img.mlx_img, 0, 0);
	handle_time(game);
	init_sprites(game);
	init_weapons(game);
	load_grid(game);
	load_map_debug(game);
	clear_z_buffer(game);
	init_threads(game);
	//close_window(game);
}
