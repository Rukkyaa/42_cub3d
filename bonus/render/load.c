/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:38:26 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/06 12:45:20 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_y(t_game *game, int *y, int *y_end)
{
	if ((int)(game->player.pos.y / 64) - 3 < 0)
	{
		*y = -1;
		*y_end = 7;
	}
	else if ((int)(game->player.pos.y / 64) + 4 > map_heigth(game->map))
	{
		*y = map_heigth(game->map) - 8;
		*y_end = map_heigth(game->map);
	}
	else
	{
		*y = (int)(game->player.pos.y / 64) - 4;
		*y_end = (int)(game->player.pos.y / 64) + 4;
	}
}

void	get_x(t_game *game, int *x, int *x_end)
{
	if ((int)(game->player.pos.x / 64) - 3 < 0)
	{
		*x = -1;
		*x_end = 7;
	}
	else if ((int)(game->player.pos.x / 64) + 4 > map_width(game->map))
	{
		*x = map_width(game->map) - 8;
		*x_end = map_width(game->map);
	}
	else
	{
		*x = (int)(game->player.pos.x / 64) - 4;
		*x_end = (int)(game->player.pos.x / 64) + 4;
	}
}

void	load_map(t_game *game)
{
	int			x;
	int			y;
	int			x_end;
	int			y_end;
	t_vector	pos;
	t_vector	size;

	pos.x = 0;
	pos.y = 0;
	get_y(game, &y, &y_end);
	while (++y < map_heigth(game->map) && y < y_end)
	{
		get_x(game, &x, &x_end);
		// if (x != -1 && x != map_width(game->map) - 8)
		// {
		// 	size.y = 32;
		// 	size.x = 32 - (int)game->player.pos.x % 64 / 2;
		// 	if (is_wall(game->map[y][x]))
		// 		draw_filled_rectangle(game, pos, size, BLUE_PIXEL);
		// 	else
		// 		draw_filled_rectangle(game, pos, size, GREEN_PIXEL);
		// 	pos.x = 32 - (int)game->player.pos.x % 64 / 2;
		// }
		while (++x < (map_width(game->map)) && x < x_end)
		{
			if (is_wall(game->map[y][x]))
				draw_filled_square(game, pos, 32, BLUE_PIXEL);
			else if (game->map[y][x] == '0')
				draw_filled_square(game, pos, 32, GREEN_PIXEL);
			else
				draw_filled_square(game, pos, 32, 888888);
			pos.x += 32;
		}
		// if (x_end != 7 && x_end != map_width(game->map))
		// {
		// 	size.y = 32;
		// 	size.x = (int)game->player.pos.x % 64 / 2;
		// 	if (is_wall(game->map[y][x]))
		// 		draw_filled_rectangle(game, pos, size, BLUE_PIXEL);
		// 	else
		// 		draw_filled_rectangle(game, pos, size, GREEN_PIXEL);
		// }
		pos.x = 0;
		pos.y += 32;
	}
}
