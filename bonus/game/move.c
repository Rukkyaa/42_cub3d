/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:49:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/27 15:34:16 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_player_tile_pos(t_player	*player)
{
	player->tile_pos.x = (int) ( player->pos.x / 64 );
	player->tile_pos.y = (int) ( player->pos.y / 64 );
}

void	update_player_state(int key_states[256], t_game *game)
{
	if (key_states['w'] || key_states['s'] || key_states['a'] || key_states['d'])
		game->player.sound_state.player_state = WALKING_STATE;
	else
		game->player.sound_state.player_state = IDLE_STATE;
	if (key_states[2] && key_states['w'])
		game->player.sound_state.player_state = RUNNING_STATE;
}

void	player_mob_collide(t_game *game,  t_sprite *mob)
{
	t_vector3d	next_pos_a;	
	t_vector3d	next_pos_b;	
	float  distance;
	int  	collide_dist;
	if(game->player.jumping)
		collide_dist = 7;
	else
		collide_dist = 10;

	next_pos_a = vec_sum(mob->pos, mob->speed);
	next_pos_b = vec_sum(game->player.pos, game->player.speed);
	distance = vec_distance(next_pos_a, next_pos_b);
	if (distance < 10)
	{
		mob->speed.x = 0;
		mob->speed.x = 0;
		game->player.speed.x = 0;
		game->player.speed.y = 0;
	}
}

void	player_mobs_collide(t_game *game,  t_sprite *sprites)
{
	t_sprite		*tmp;

	tmp = sprites;
	while (tmp)
	{
		if (tmp->type == MOB && tmp->state != DEATH)
			player_mob_collide(game, tmp);
		tmp = tmp->next;
	}
}


void	edit_player_pos(t_game *game)
{
	t_vector3d right = vec_rotate(game->player.direction, 90);
	t_vector3d left = vec_rotate(game->player.direction, 270);

	if(game->key_states[32] && game->player.jumping == 0)
	{
		game->player.jumping = 1;
		game->player.start_jump = game->frame_count;
	}
	if(game->player.jumping == 1)
	{
		if(game->frame_count - game->player.start_jump < 5)
			game->player.pos3d.z += 3;
		else if (game->frame_count - game->player.start_jump < 9)
			game->player.pos3d.z += 0;
		else if (game->player.pos3d.z > 32)
			game->player.pos3d.z -= 2;
		else
			game->player.jumping = 0;
	}
	if (game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.direction, 1);
	else if (game->key_states['s'] )
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
	if(game->key_states[2] && game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.speed, game->player.velocity * 2 * game->time.delta_frame_ms / 1000.0f);
	else
		game->player.speed = vec_scalar_mult(game->player.speed, game->player.velocity * game->time.delta_frame_ms / 1000.0f);
	player_collides(game, game->player.speed);
	player_mobs_collide(game, game->sprites);
	game->player.pos = vec_sum(game->player.pos, game->player.speed);
	game->player.speed.x = 0;
	game->player.speed.y = 0;
	update_player_state(game->key_states, game);
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
	game->player.angle = fmod((game->player.angle + 360) , 360);
}

void	edit_player_rotate(t_game *game)
{
	
	if (game->key_states[0])
		rotate_player(game, -3);
	if (game->key_states[1])
		rotate_player(game, 3);
	if(game->mouse_move)
	{
		rotate_player(game, game->mouse_diff.x / 50);
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
	// if (game->key_states['r'])
	// {
	// 	if( game->player.pos3d.z < game->wall_height - 1)
	// 	{
	// 		game->player.pos3d.z += 1;
	// 					//game->player.tilt += 1;
	// 		// printf("pos : %f\n", game->player.pos3d.z);
	// 	}
	// }
	// if (game->key_states['f'])
	// {
	// 	if( game->player.pos3d.z > 1)
	// 	{
	// 		game->player.pos3d.z -= 1;
	// 		//game->camera.plane_center.y = game->player.pos3d.z + game->camera.p_plane_dist * cosf(M_PI/2) ;
	// 		//game->player.tilt -= 1;
	// 		// printf("pos : %f\n", game->player.pos3d.z);
	// 	}
	// }
}
