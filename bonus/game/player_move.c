/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:49:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/01 22:34:38 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_player_tile_pos(t_player *player)
{
	player->tile_pos.x = (int)(player->pos.x / 64);
	player->tile_pos.y = (int)(player->pos.y / 64);
}

void	update_player_state(int key_states[256], t_game *game)
{
	if (key_states['w'] || key_states['s'] || key_states['a']
		|| key_states['d'])
		game->player.sound_state.player_state = WALKING_STATE;
	else
		game->player.sound_state.player_state = IDLE_STATE;
	if (key_states[2] && key_states['w'])
		game->player.sound_state.player_state = RUNNING_STATE;
}

void	player_jump(t_game *game)
{
	if (game->key_states[32] && game->player.jumping == 0)
	{
		game->player.jumping = 1;
		game->player.start_jump = game->frame_count;
	}
	if (game->player.jumping == 1)
	{
		if (game->frame_count - game->player.start_jump < 5)
			game->player.pos3d.z += 3;
		else if (game->frame_count - game->player.start_jump < 9)
			game->player.pos3d.z += 0;
		else if (game->player.pos3d.z > 32)
			game->player.pos3d.z -= 2;
		else
			game->player.jumping = 0;
	}
}

void	set_player_direction(t_game *game)
{
	t_vector3d	right;
	t_vector3d	left;

	right = vec_rotate(game->player.direction, 90);
	left = vec_rotate(game->player.direction, 270);
	if (game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.direction, 1);
	else if (game->key_states['s'])
		game->player.speed = vec_scalar_mult(game->player.direction, -1);
	if (game->key_states['a'] && !game->player.jumping)
	{
		game->player.speed = vec_sum(game->player.speed, left);
		game->player.speed = vec_normalize(game->player.speed);
	}
	else if (game->key_states['d'] && !game->player.jumping)
	{
		game->player.speed = vec_sum(game->player.speed, right);
		game->player.speed = vec_normalize(game->player.speed);
	}
}

void	edit_player_pos(t_game *game)
{
	player_jump(game);
	set_player_direction(game);
	if (game->key_states[2] && game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.speed,
				game->player.velocity * 2
				* game->time.delta_frame_ms
				/ 1000.0f);
	else
		game->player.speed = vec_scalar_mult(game->player.speed,
				game->player.velocity
				* game->time.delta_frame_ms
				/ 1000.0f);
	player_wall_collides(game, game->player.speed);
	player_mobs_collide(game, game->sprites);
	player_doors_open(game);
	game->player.pos = vec_sum(game->player.pos, game->player.speed);
	game->player.speed.x = 0;
	game->player.speed.y = 0;
	update_player_state(game->key_states, game);
	update_player_tile_pos(&game->player);
}
