/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:49:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/14 10:09:30 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_player_tile_pos(t_player	*player)
{
	player->tile_pos.x = (int) ( player->pos.x / 64 );
	player->tile_pos.y = (int) ( player->pos.y / 64 );
}

void	edit_player_pos(t_game *game)
{
	t_vector3d right = vec_rotate(game->player.direction, 90);
	t_vector3d left = vec_rotate(game->player.direction, 270);

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
		game->player.speed = vec_scalar_mult(game->player.speed, game->player.velocity * 2 * game->time.delta_frame_ms / 1000.0f);
	else
		game->player.speed = vec_scalar_mult(game->player.speed, game->player.velocity * game->time.delta_frame_ms / 1000.0f);
	player_collides(game, game->player.speed);
	game->player.pos = vec_sum(game->player.pos, game->player.speed);
	game->player.speed.x = 0;
	game->player.speed.y = 0;
	update_player_tile_pos(&game->player);
}

void		player_collides(t_game *game, t_vector3d speed)
{
	t_vector3d	v_offset;
	t_vector3d	vi_pos;
	t_vector3d	vi_pos_add_offset;
	
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
	if(game->mouse_move)
	{
		rotate_player(game, game->mouse_diff.x / 40);
		game->camera.plane_center.y -=  game->mouse_diff.y / 4;
		// vec_print(&game->mouse_diff, "mouse diff");
		game->mouse_diff.x = 0;
		game->mouse_diff.y = 0;
		// rotate_player(game, game->mouse_diff.x * game->time.delta_frame_ms / 2000.0f);
		// game->camera.plane_center.y -=  game->mouse_diff.y * game->time.delta_frame_ms  / 150.0f;
		game->mouse_move = 0;
		if(game->camera.plane_center.y > 750)
			game->camera.plane_center.y = 750;
		if(game->camera.plane_center.y < 150)
			game->camera.plane_center.y = 150;
	}
	game->player.angle = fmod((game->player.angle + 360) , 360);
	if (game->key_states['r'])
	{
		if( game->player.pos3d.z < game->wall_height - 1)
		{
			game->player.pos3d.z += 1;
						//game->player.tilt += 1;
			// printf("pos : %f\n", game->player.pos3d.z);
		}
	}
	if (game->key_states['f'])
	{
		if( game->player.pos3d.z > 1)
		{
			game->player.pos3d.z -= 1;
			//game->camera.plane_center.y = game->player.pos3d.z + game->camera.proj_plane_distance * cosf(M_PI/2) ;
			//game->player.tilt -= 1;
			// printf("pos : %f\n", game->player.pos3d.z);
		}
	}
}
