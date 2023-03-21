/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/21 16:50:16 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_xpm_to_img(t_game *game, t_img *img, char *path)
{
	//printf("%s\n", path);
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
		&img->width, &img->heigth);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
}

void	load_img(t_game *game)
{
	// ft_xpm_to_img(&game->texture.wall1, "images/pjay2.xpm");
	ft_xpm_to_img(game, &game->texture.wall1, "images/retro_texture_pack/CRATE_1L.xpm");
	ft_xpm_to_img(game, &game->texture.wall2, "images/retro_texture_pack/CRATE_1M.xpm");
	ft_xpm_to_img(game, &game->texture.wall3, "images/retro_texture_pack/DOOR_2A.xpm");
	ft_xpm_to_img(game, &game->texture.wall4, "images/retro_texture_pack/CRATE_1J.xpm");
	
	// ft_xpm_to_img(game, &game->texture.wall1, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall2, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall3, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall4, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall1, "images/pjay2.xpm");
	// ft_xpm_to_img(game, &game->texture.wall2,  "images/pjay2.xpm");
	// ft_xpm_to_img(game, &game->texture.wall3,  "images/pjay2.xpm");
	// ft_xpm_to_img(game, &game->texture.wall4,  "images/pjay2.xpm");

	ft_xpm_to_img(game,  &game->texture.ground, "images/retro_texture_pack/TILE_3E.xpm");
	//ft_xpm_to_img(game, &game->texture.roof, "images/retro_texture_pack/WARN_1.xpm");
	// ft_xpm_to_img(game, &game->texture.ground, "images/SBS_tiny_XPM/Tile/Tile_09-512x512.xpm");
	
	ft_xpm_to_img(game,  &game->texture.roof, "images/retro_texture_pack/CONCRETE_1A.xpm");
	ft_xpm_to_img(game, &game->inventory.img, "images/inventory.xpm");
	ft_xpm_to_img(game, &game->weapon.sword, "images/weapons/longsword.xpm");
	ft_xpm_to_img(game, &game->weapon.axe, "images/weapons/axe.xpm");
	ft_xpm_to_img(game, &game->hud.aim, "images/aim_white_simple.xpm");
	// ft_xpm_to_img(game, &game->hud.weapon, "images/weapons/shotgun.xpm");
	ft_xpm_to_img(game, &game->hud.weapon, "images/weapons/transparent.xpm");
	// ft_xpm_to_img(game, &game->hud.aim, "images/aim_red.xpm");
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
	t_animation zombie_animation;
	zombie_animation.imgs = fill_sprite_animation(game, "images/FPS_pixel_zombie/RUN_SLICED_XPM");
	zombie_animation.current_img = zombie_animation.imgs[0];
	zombie_animation.frame_duration_ms = 30;
	zombie_animation.nb_imgs = 48;
	zombie_animation.start_time_ms = game->time.frame.tv_sec * 1000 + game->time.frame.tv_usec / 1000;
	while(i < 10)
	{
		// ft_xpm_to_img(game, &game->sprites[i].texture, "images/monster1.xpm");
		// printf("bpp : %d\n", game->sprites[i].texture.bpp);
		game->sprites[i].pos.x = ((double)rand() / (double)RAND_MAX) * map_width(game->map) * 64;
		game->sprites[i].pos.y = ((double)rand() / (double)RAND_MAX) * map_heigth(game->map) * 64;
		// game->sprites[i].pos.x = 10 * 64;
		// game->sprites[i].pos.y = (i + 10) * 64;
		vec_print(&game->sprites[i].pos, "sprite pos");
		// game->sprites[i].img_run = zombie_animation.imgs;
		// game->sprites[i].current_img = malloc(sizeof(t_img));
		game->sprites[i].animation = zombie_animation;
		game->sprites[i].animation.frame_offset = ((double)rand() / (double)RAND_MAX) * zombie_animation.nb_imgs;
		//ft_xpm_to_img(game, game->sprites[i].current_img, "images/monster1.xpm");
		game->sprites[i].pos.z = -5;
		game->sprites[i].height = 70;
		game->sprites[i].width = game->sprites[i].height * (game->sprites[i].animation.current_img->width) / (game->sprites[i].animation.current_img->heigth);
		
		vec_print(&game->sprites[i].pos, "sprite pos");
		game->sprites[i].distance = 100;
		i++;
	}
}

void init_weapons(t_game *game)
{
	int i = 0;
	t_animation grap_gun;
	grap_gun.imgs = fill_sprite_animation(game, "images/weapons/Grap_gun_upscale_xpm_alpha_resized_fuzz");
	grap_gun.current_img = grap_gun.imgs[0];
		printf("anim\n");
	grap_gun.frame_duration_ms = 100;
	grap_gun.nb_imgs = 16;
	grap_gun.start_time_ms = game->time.frame.tv_sec * 1000 + game->time.frame.tv_usec / 1000;
	game->hud.weapon_anim = grap_gun;
}


void	precompute_raycast(t_game *game)
{
	int i = 0;
	float angle;
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


void	var_init(t_game *game)
{
	int i = 256;
	while(i--)
		game->key_states[i] = 0;
	i = 256;
	while(i--)
		game->key_release_states[i] = 1;
	game->debug_win = mlx_new_window( _mlx()->mlx, map_width(game->map) * 64, map_heigth(game->map) * 64, "map");
	game->mlx = _mlx()->mlx;
	game->player.pos.x = 3*64 + 32;
	game->player.pos.y = 3*64 + 32; 
	game->player.collision_pos.x = game->player.pos.x + 32;
	game->player.collision_pos.y = game->player.pos.y + 32;
	game->player.pos3d.x = 3*64 + 32;
	game->player.pos3d.y = 3*64 + 32; 
	game->player.pos3d.z = 32;
	game->player.direction.x = 1;
	game->player.direction.y = 0; 
	game->player.tilt = 0; 
	game->player.angle = 0; 
	game->player.speed.x = 0;
	game->player.speed.y = 0; 
	game->player.direction_adjust = 10; 
	game->frame_count = 0;
	game->time.delta_frame_ms = 1;
	game->time.fps = 0;
	game->wall_height = 64;
	// angle_to_vector( M_PI / 4, &game->player.direction);
    vec_print(&game->player.direction, "player dir");
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
	init_camera(&game->camera);
	game->wall_height_x_proj_dist = game->wall_height * game->camera.proj_plane_distance;
	game->mouse.x = 0;
	game->mouse.y = 0;
	precompute_raycast(game);
	pre_compute_resize(game);
	load_img(game);
	load_map(game);
	load_sounds(&game->sounds);
	init_basic_vectors(game);
	init_inventory(game);
	mlx_put_image_to_window(game->mlx, _mlx()->win, _mlx()->img.mlx_img, 0, 0);
	handle_time(game);
	init_sprites(game);
	init_weapons(game);
	load_grid(game);
	load_map_debug(game);
}
