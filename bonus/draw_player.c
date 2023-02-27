/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:23:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:52:42 by teliet           ###   ########.fr       */
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
	// cast_2D_ray(game);
	draw_player_direction(game, color);
	draw_filled_circle(&game->img, game->player.pos, 5, color);
	draw_filled_circle(&game->img, game->player.collision_pos, 5, color);
}
