/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 14:39:17 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	var_init(t_game *game)
{
	int i = 256;
	while(i--)
		game->key_states[i] = 0;
	i = 256;
	while(i--)
		game->key_release_states[i] = 1;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 8 * 64, 8 * 64, "cub3d");
	game->player.pos.x = 100;
	game->player.pos.y = 100;
	game->player.direction.x = 1;
	game->player.direction.y = 1;
	game->img.mlx_img = mlx_new_image(game->mlx, 8 * 64, 8 * 64);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	load_map(game);
	load_grid(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
}
