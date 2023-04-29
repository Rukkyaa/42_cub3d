/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:49:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/29 16:39:13 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	rotate_player(t_game *game, float angle)
{
	vec_rotate_edit(&(game->player.direction), angle);
	vec_rotate_edit(&(game->camera.plane), angle);
	game->player.angle += angle;
	game->player.angle = fmod((game->player.angle + 360), 360);
}

void	edit_player_rotate(t_game *game)
{
	if (game->key_states[0])
		rotate_player(game, -3);
	if (game->key_states[1])
		rotate_player(game, 3);
	if (game->mouse_move)
	{
		rotate_player(game, game->mouse_diff.x / 50 * MOUSE_SENSITIVITY);
		game->camera.plane_center.y -= game->mouse_diff.y / 4
			* MOUSE_SENSITIVITY;
		game->mouse_diff.x = 0;
		game->mouse_diff.y = 0;
		game->mouse_move = 0;
		if (game->camera.plane_center.y > 750)
			game->camera.plane_center.y = 750;
		if (game->camera.plane_center.y < 150)
			game->camera.plane_center.y = 150;
	}
}
