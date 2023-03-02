/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:23:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/02 23:16:41 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_player_direction(t_game *game, int color)
{
	t_vector point;
	point.x = (int) (game->player.pos.x + game->player.direction.x * 10.0f);
	point.y = (int) (game->player.pos.y + game->player.direction.y * 10.0f);
	
	draw_line_dda(&game->img, game->player.pos, point, color);	
}

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
	draw_filled_circle(&game->fps_img, pos, 5, color);
}
