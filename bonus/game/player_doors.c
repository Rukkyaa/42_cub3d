/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:34:14 by theo              #+#    #+#             */
/*   Updated: 2023/05/01 22:34:46 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_door(t_game *game, int x, int y)
{
	t_door	*door;

	if (game->map[y][x] == 'D')
	{
		door = game->doors[(int)(y * map_width(game->map) + x)];
		game->player.near_door = 1;
		if (game->key_states['x'] == 1)
		{
			game->key_states['x'] = 0;
			if (door->state == OPEN)
				door->state = CLOSING;
			if (door->state == CLOSED)
				door->state = OPENING;
		}
	}
}

void	player_doors_open(t_game *game)
{
	t_vector3d	pos_tile;

	game->player.near_door = 0;
	pos_tile = pixel_to_tile(game->player.pos);
	check_door(game, pos_tile.x, pos_tile.y + 1);
	check_door(game, pos_tile.x + 1, pos_tile.y);
	check_door(game, pos_tile.x, pos_tile.y - 1);
	check_door(game, pos_tile.x - 1, pos_tile.y);
}
