/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 11:58:48 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			if (game->map[i][j] == '1')
				draw_filled_square(game, j * 64, i * 64, 64, BLUE_PIXEL);
			else
				draw_filled_square(game, j * 64, i * 64, 64, GREEN_PIXEL);
		}
	}
}

void	var_init(t_game *game)
{
	int i = 256;
	while(--i)
		game->key_states[i] = 0;
	i = 256;
	while(--i)
		game->key_release_states[i] = 1;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 8 * 64, 8 * 64, "cub3d");
	game->player.pos.x = 100;
	game->player.pos.y = 100;
	game->player.direction.x = 1;
	game->player.direction.y = 1;
	load_map(game);
	load_grid(game);
}
