/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:23:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/20 16:46:08 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_player_direction(t_game *game, int color)
{
	t_vector point;
	point.x = (int) (game->player.pos.x + game->player.direction.x * 100.0f);
	point.y = (int) (game->player.pos.y + game->player.direction.y * 100.0f);
	
	draw_line(game, game->player.pos, point, 3, color);	
}

void	draw_player(t_game *game, int color)
{
	// cast_2D_ray(game);
	// draw_player_direction(game, color);
	draw_filled_circle(&game->img, game->player.pos, 5, color);
}

void	move(t_game *game, char direction)
{

	draw_filled_circle(&game->img, game->player.pos, 10, GREEN_PIXEL);
	draw_player_direction(game, GREEN_PIXEL);
	// draw_line(game, game->player.pos, game->player.direction, 3, GREEN_PIXEL);	
	if (direction == 'N')
		game->player.pos.y -= 2;
	else if (direction == 'S')
		game->player.pos.y += 2;
	else if (direction == 'W')
		game->player.pos.x -= 2;
	else
		game->player.pos.x += 2;
	draw_filled_circle(&game->img, game->player.pos, 10, RED_PIXEL);
	// draw_line(game, game->player.pos, game->player.direction, 3, RED_PIXEL);	
	draw_player_direction(game, RED_PIXEL);
	// }
}
