/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/08 12:33:46 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_xpm_to_img(t_img *texture, char *path)
{
	texture->mlx_img = mlx_xpm_file_to_image(_mlx()->mlx, path,
		&texture->width, &texture->heigth);
	texture->addr = mlx_get_data_addr(texture->mlx_img, &texture->bpp,
			&texture->line_len, &texture->endian);
}

void	load_img(t_game *game)
{
	// ft_xpm_to_img(&game->texture.wall1, "images/pjay2.xpm");
	ft_xpm_to_img(&game->texture.wall1, "images/retro_texture_pack/CRATE_1L.xpm");
	ft_xpm_to_img(&game->texture.wall2, "images/retro_texture_pack/CRATE_1M.xpm");
	ft_xpm_to_img(&game->texture.wall3, "images/retro_texture_pack/DOOR_2A.xpm");
	ft_xpm_to_img(&game->texture.wall4, "images/retro_texture_pack/CRATE_1J.xpm");
	ft_xpm_to_img(&game->texture.ground, "images/retro_texture_pack/FLOOR_1C.xpm");
	ft_xpm_to_img(&game->texture.roof, "images/retro_texture_pack/SUPPORT_3A.xpm");
	ft_xpm_to_img(&game->inventory.img, "images/inventory.xpm");
	ft_xpm_to_img(&game->weapon.sword, "images/weapons/longsword.xpm");
}

void	init_camera(t_camera *camera)
{
	camera->proj_plane_height =  10;
	camera->proj_plane_width =  camera->proj_plane_height * ( (float) RES_X / (float) RES_Y);
	camera->proj_plane_distance = ((float) camera->proj_plane_width / 2.0f) / tanf(FOV_RADIANS / 2.0f);
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

void	var_init(t_game *game)
{
	int i = 256;
	while(i--)
		game->key_states[i] = 0;
	i = 256;
	while(i--)
		game->key_release_states[i] = 1;
	game->player.pos.x = 3*64 + 32;
	game->player.pos.y = 3*64 + 32; 
	game->player.collision_pos.x = game->player.pos.x + 32;
	game->player.collision_pos.y = game->player.pos.y + 32;
	game->player.pos3d.x = 3*64 + 32;
	game->player.pos3d.y = 3*64 + 32; 
	game->player.pos3d.z = 64;
	game->player.direction.x = 1;
	game->player.direction.y = 0; 
	game->player.speed.x = 0;
	game->player.speed.y = 0; 
	game->player.direction_adjust = 10; 
	game->time_inc = 150;
	game->time.delta_frame_ms = 1;
    vec_print(&game->player.direction, "player dir");
	init_camera(&game->camera);
	game->mouse.x = 0;
	game->mouse.y = 0;
	load_img(game);
	load_map(game);
	load_sounds(&game->sounds);
	init_basic_vectors(game);
	init_inventory(game);
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->win, _mlx()->img.mlx_img, 0, 0);
}
