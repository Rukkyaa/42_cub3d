/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:38:26 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/02 22:42:11 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_map(t_game *game)
{
	int			x;
	int			y;
	int			x_end;
	int			y_end;
	t_vector	pos;

	pos.x = 0;
	pos.y = 0;
	if ((int)(game->player.pos.y / 64) - 3 < 0)
	{
		y = -1;
		y_end = 7;
	}
	else if ((int)(game->player.pos.y / 64) + 4 > map_heigth(game->map))
	{
		y = map_heigth(game->map) - 8;
		y_end = map_heigth(game->map);
	}
	else
	{
		y = (int)(game->player.pos.y / 64) - 4;
		y_end = (int)(game->player.pos.y / 64) + 4;
	}
	while (++y < map_heigth(game->map) && y < y_end)
	{
		if ((int)(game->player.pos.x / 64) - 3 < 0)
		{
			x = -1;
			x_end = 7;
		}
		else if ((int)(game->player.pos.x / 64) + 4 > map_width(game->map))
		{
			x = map_width(game->map) - 8;
			x_end = map_width(game->map);
		}
		else
		{
			x = (int)(game->player.pos.x / 64) - 4;
			x_end = (int)(game->player.pos.x / 64) + 4;
		}
		while (++x < (map_width(game->map)) && x < x_end)
		{
			pos.x *= 32;
			pos.y *= 32;
			if (game->map[y][x] == '1')
				draw_filled_square(game, pos, 32, BLUE_PIXEL);
			else if (game->map[y][x] == '0')
				draw_filled_square(game, pos, 32, GREEN_PIXEL);
			else
				draw_filled_square(game, pos, 32, 888888);
			pos.x = pos.x / 32 + 1;
			pos.y = pos.y / 32;
		}
		pos.x = 0;
		pos.y += 1;
	}
}
