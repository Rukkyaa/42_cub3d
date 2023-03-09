/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:49:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 15:37:41 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	edit_player_pos(t_game *game)
{
	t_vector right = vec_rotate(game->player.direction, 90);
	t_vector left = vec_rotate(game->player.direction, 270);

	if (player_moving(game) && game->key_states[2] == 1)
	{
		ma_device_stop(&game->sounds.footstep.device);
		ma_device_start(&game->sounds.dejavu.device);
	}
	else if (player_moving(game))
	{
		ma_device_start(&game->sounds.footstep.device);
		ma_device_stop(&game->sounds.dejavu.device);
	}
	else
	{
		ma_device_stop(&game->sounds.footstep.device);
		ma_device_stop(&game->sounds.dejavu.device);
	}
	if (game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.direction, 1);
	else if (game->key_states['s'] )
		game->player.speed = vec_scalar_mult(game->player.direction, -1);
	if (game->key_states['a'])
	{
		game->player.speed = vec_sum(game->player.speed, left);
		game->player.speed = vec_normalize(game->player.speed);
	}
	else if (game->key_states['d'])
	{
		game->player.speed = vec_sum(game->player.speed, right);
		game->player.speed = vec_normalize(game->player.speed);
	}
	if(game->key_states[2] && game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.speed, 200 * game->time.delta_frame_ms / 1000.0f);
	else
		game->player.speed = vec_scalar_mult(game->player.speed, 100 * game->time.delta_frame_ms / 1000.0f);
	player_collides(game, game->player.speed);
	game->player.pos = vec_sum(game->player.pos, game->player.speed);
	game->player.speed.x = 0;
	game->player.speed.y = 0;
}

void		player_collides(t_game *game, t_vector speed)
{
	t_vector	v_offset;
	t_vector	vi_pos;
	t_vector	vi_pos_add_offset;
	
	v_offset.x = 0;
	v_offset.y = 0;
	if (speed.x > 0)
		v_offset.x = 25;
	else
		v_offset.x = -25;
	if (speed.y > 0)
		v_offset.y = 25;
	else
		v_offset.y = -25;
	vi_pos = pixel_to_tile(game->player.pos);
	vi_pos_add_offset = pixel_to_tile(vec_sum(game->player.pos, v_offset));
	if(!is_walkable(game, vi_pos_add_offset.x, vi_pos.y))
		game->player.speed.x = 0;
	if(!is_walkable(game , vi_pos.x, vi_pos_add_offset.y))
		game->player.speed.y = 0;
}

void	rotate_player(t_game *game, float angle)
{
	vec_rotate_edit(&(game->player.direction), angle);
	vec_rotate_edit(&(game->camera.plane), angle);
	game->player.angle += angle;
}

void	edit_player_rotate(t_game *game)
{
	if (game->key_states[0])
		rotate_player(game, -3);
	if (game->key_states[1])
		rotate_player(game, 3);
	game->player.angle = fmod((game->player.angle + 360) , 360);
	if (game->key_states['r'])
		game->player.pos3d.z += 1;
	if (game->key_states['f'])
		game->player.pos3d.z -= 1;
}
