/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 17:18:01 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	create_img(char *path)
{
	t_garbage	*gc_img;
	t_img		img;

	gc_img = _gc_img();
	img.mlx_img = mlx_xpm_file_to_image(_game()->mlx, path,
			&img.width, &img.heigth);
	if (!img.mlx_img)
		free_garbage(XPM_ERROR);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp,
			&img.line_len, &img.endian);
	if (!img.addr)
		free_garbage(ADDR_ERROR);
	gc_add_back(&gc_img, gc_new(img.mlx_img));
	return (img);
}

// void	ft_xpm_to_img(t_game *game, t_img *texture, char *path)
// {
// 	texture->mlx_img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
// 			&texture->heigth);
// 	texture->addr = mlx_get_data_addr(texture->mlx_img, &texture->bpp,
// 			&texture->line_len, &texture->endian);
// }

void	load_img(t_game *game)
{
	game->texture.north = create_img(game->parsing->no);
	game->texture.south = create_img(game->parsing->so);
	game->texture.west = create_img(game->parsing->we);
	game->texture.east = create_img(game->parsing->ea);
}

void	init_player(t_game *game)
{
	game->player.pos.x = (int)game->parsing->player_pos.x * 64 + 32;
	game->player.pos.y = (int)game->parsing->player_pos.y * 64 + 32;
	game->player.speed.x = 0;
	game->player.speed.y = 0;
	game->player.collision_pos.x = game->player.pos.x + 32;
	game->player.collision_pos.y = game->player.pos.y + 32;
	game->player.direction.x = 0;
	game->player.direction.y = 0;
	if (game->parsing->player_dir == 'N')
		game->player.direction.y = -1;
	else if (game->parsing->player_dir == 'S')
		game->player.direction.y = 1;
	else if (game->parsing->player_dir == 'W')
		game->player.direction.x = -1;
	else if (game->parsing->player_dir == 'E')
		game->player.direction.x = 1;

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
	_game()->map = _game()->parsing->map;
	_game()->texture.sky_color = 0x29b3e0;
	_game()->texture.floor_color = 0x3ecc3e;
	load_img(_game());
	mlx_put_image_to_window(_game()->mlx, _game()->fps_win,
		_game()->fps_img.mlx_img, 0, 0);
}
