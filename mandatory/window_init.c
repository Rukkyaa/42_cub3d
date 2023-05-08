/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 14:10:12 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_xpm_to_img(t_game *game, t_img *texture, char *path)
{
	texture->mlx_img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->heigth);
	texture->addr = mlx_get_data_addr(texture->mlx_img, &texture->bpp,
			&texture->line_len, &texture->endian);
}

void	load_img(t_game *game)
{
	ft_xpm_to_img(game, &game->texture.wall,
		"images/retro_texture_pack/HEDGE_1A.xpm");
	ft_xpm_to_img(game, &game->texture.north,
		"images/retro_texture_pack/HEDGE_1A.xpm");
	ft_xpm_to_img(game, &game->texture.east,
		"images/retro_texture_pack/HEDGE_1B.xpm");
	ft_xpm_to_img(game, &game->texture.west,
		"images/retro_texture_pack/HEDGE_1C.xpm");
	ft_xpm_to_img(game, &game->texture.south,
		"images/retro_texture_pack/HEDGE_2A.xpm");
}

void	init_player(t_game *game)
{
	game->player.pos.x = 3 * 64 + 32;
	game->player.pos.y = 3 * 64 + 32;
	game->player.speed.x = 0;
	game->player.speed.y = 0;
	game->player.collision_pos.x = game->player.pos.x + 32;
	game->player.collision_pos.y = game->player.pos.y + 32;
	game->player.direction.x = 1;
	game->player.direction.y = 0;
	game->player.direction_adjust = 10;
}

void	var_init(void)
{
	int	i;

	i = 256;
	while (i--)
	{
		_game()->key_states[i] = 0;
		_game()->key_release_states[i] = 1;
	}
	init_player(_game());
	_game()->texture.sky_color = 0x29b3e0;
	_game()->texture.floor_color = 0x3ecc3e;
	load_img(_game());
	mlx_put_image_to_window(_game()->mlx, _game()->fps_win, _game()->fps_img.mlx_img, 0,
		0);
}
