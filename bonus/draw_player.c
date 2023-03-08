/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:23:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/08 11:56:01 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_player(t_game *game, int color)
{
	t_vector	pos;

	if ((int)(game->player.pos.y / 64) < 3)
		pos.y = game->player.pos.y;
	else if ((int)(game->player.pos.y / 64) + 4 > map_heigth(game->map))
		pos.y = game->player.pos.y - (map_heigth(game->map) - 7) * 64;
	else
		pos.y = 64 * 3 + 32;
	if ((int)(game->player.pos.x / 64) < 3)
		pos.x = game->player.pos.x;
	else if ((int)(game->player.pos.x / 64) + 4 > map_width(game->map))
		pos.x = game->player.pos.x - (map_width(game->map) - 7) * 64;
	else
		pos.x = 64 * 3 + 32;
	draw_filled_circle(&_mlx()->img, pos, 5, color);
}
