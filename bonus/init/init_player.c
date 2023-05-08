/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:53:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/08 17:43:01 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_player_two(t_game *game)
{
	game->player.max_hp = 100;
	game->player.hp = 100;
	game->player.death_time = 0;
	game->player.real_death_time = 0;
	game->player.lethal_hits = 0;
	game->player.weapon_selected = 0;
	game->player.cocaine = false;
	game->player.bonus_strength = 0;
	game->player.velocity = 100;
	game->player.near_door = 0;
	game->player.jumping = 0;
}

void	init_player(t_game *game)
{
	game->player.pos.x = 28 * 64 + 32;
	game->player.pos.y = 4 * 64 + 32;
	game->player.pos.z = 0;
	game->player.collision_pos.x = game->player.pos.x + 32;
	game->player.collision_pos.y = game->player.pos.y + 32;
	game->player.pos3d.x = 1 * 64 + 32;
	game->player.pos3d.y = 1 * 64 + 32;
	game->player.pos3d.z = 32;
	game->player.direction.x = 1;
	game->player.direction.y = 0;
	game->player.direction.z = 0;
	game->player.tilt = 0;
	game->player.angle = vec_angle(game->v_left, game->player.direction)
		* 180.0f / M_PI;
	game->player.speed.x = 0;
	game->player.speed.y = 0;
	game->player.speed.z = 0;
	game->player.direction_adjust = 10;
	init_player_two(game);
}
