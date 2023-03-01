/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/01 16:57:14 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_xpm_to_img(t_game *game, t_img *texture, char *path)
{
	texture->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
		&texture->width, &texture->heigth);
	texture->addr = mlx_get_data_addr(texture->mlx_img, &texture->bpp,
			&texture->line_len, &texture->endian);
}

void	load_img(t_game *game)
{
	ft_xpm_to_img(game, &game->texture.wall, "images/pjay2.xpm");
	ft_xpm_to_img(game, &game->texture.ground, "images/retro_texture_pack/FLOOR_1C.xpm");
	// ft_xpm_to_img(game, &game->texture.roof, "images/retro_texture_pack/FLOOR_1C.xpm");
	
	// ft_xpm_to_img(game, &game->texture.wall, "images/wall.xpm");
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
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, map_width(game->map) * 64, map_heigth(game->map) * 64, "map");
	game->fps_win = mlx_new_window(game->mlx, RES_X, RES_Y, "first_person");
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
	// angle_to_vector( M_PI / 4, &game->player.direction);
    vec_print(&game->player.direction, "player dir");
	// close_window(game);
	game->img.mlx_img = mlx_new_image(game->mlx, map_width(game->map) * 64, map_heigth(game->map) * 64);
	game->fps_img.mlx_img = mlx_new_image(game->mlx, RES_X, RES_Y);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->fps_img.addr = mlx_get_data_addr(game->fps_img.mlx_img, &game->fps_img.bpp,
			&game->fps_img.line_len, &game->fps_img.endian);
	game->img.width = map_width(game->map);
	game->img.heigth = map_heigth(game->map);
	game->fps_img.width = RES_X / 64;
	game->fps_img.heigth = RES_Y / 64;
	init_camera(&game->camera);
	game->mouse.x = 0;
	game->mouse.y = 0;
	load_img(game);
	load_map(game);
	load_sounds(&game->sounds);
	load_grid(game);
	init_basic_vectors(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->fps_win, game->fps_img.mlx_img, 0, 0);
}
