/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/04 15:11:16 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_xpm_to_img(t_game *game, t_img *texture, char *path)
{
	texture->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
		&texture->width, &texture->heigth);
	texture->addr = mlx_get_data_addr(texture->mlx_img, &texture->bpp,
			&texture->line_len, &texture->endian);
}

void	load_img(t_game *game)
{
	ft_xpm_to_img(game, &game->texture.wall, "images/retro_texture_pack/HEDGE_1A.xpm");
	ft_xpm_to_img(game, &game->texture.north, "images/retro_texture_pack/HEDGE_1A.xpm");
	ft_xpm_to_img(game, &game->texture.east, "images/retro_texture_pack/HEDGE_1B.xpm");
	ft_xpm_to_img(game, &game->texture.west, "images/retro_texture_pack/HEDGE_1C.xpm");
	ft_xpm_to_img(game, &game->texture.south, "images/retro_texture_pack/HEDGE_2A.xpm");
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
	game->fps_win = mlx_new_window(game->mlx, RES_X, RES_Y, "first_person");
	game->player.pos.x = 3*64 + 32;
	game->player.pos.y = 3*64 + 32; 
	game->player.collision_pos.x = game->player.pos.x + 32;
	game->player.collision_pos.y = game->player.pos.y + 32;
	game->player.direction.x = 1;
	game->player.direction.y = 0; 
	game->player.direction_adjust = 10; 
	game->fps_img.mlx_img = mlx_new_image(game->mlx, RES_X, RES_Y);
	game->fps_img.addr = mlx_get_data_addr(game->fps_img.mlx_img, &game->fps_img.bpp,
			&game->fps_img.line_len, &game->fps_img.endian);
	game->fps_img.width = RES_X / 64;
	game->fps_img.heigth = RES_Y / 64;
	game->texture.sky_color = 0x29b3e0;
	game->texture.floor_color = 0x3ecc3e;
	load_img(game);
	mlx_put_image_to_window(game->mlx, game->fps_win, game->fps_img.mlx_img, 0, 0);
}
