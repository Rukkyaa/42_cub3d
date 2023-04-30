/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:49:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/30 14:42:52 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	player_mob_collide(t_game *game, t_sprite *mob)
{
	t_vector3d	next_pos_a;
	t_vector3d	next_pos_b;
	float		distance;
	int			collide_dist;

	if (game->player.jumping)
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

static void	player_item_collide(t_game *game, t_sprite *item)
{
	float	distance;

	distance = vec_distance(game->player.pos, item->pos);
	if (distance < 50)
	{
		if (is_consommable(item))
			use_item(game, item);
		else
			add_item(game, item->id);
		remove_entity(&game->sprites, item);
		return ;
	}
}

void	player_mobs_collide(t_game *game, t_sprite *sprites)
{
	t_sprite	*tmp;

	tmp = sprites;
	while (tmp)
	{
		if (tmp->type == MOB && tmp->state != DEATH)
			player_mob_collide(game, tmp);
		if (tmp->type == ITEM)
			player_item_collide(game, tmp);
		tmp = tmp->next;
	}
}

void	player_wall_collides(t_game *game, t_vector3d speed)
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
	vi_pos = pixel_to_tile(vec_sum(game->player.pos, game->player.speed));
	vi_pos_add_offset = pixel_to_tile(vec_sum(game->player.pos, v_offset));
	if (!is_walkable(game, vi_pos_add_offset.x, vi_pos.y))
		game->player.speed.x = 0;
	if (!is_walkable(game, vi_pos.x, vi_pos_add_offset.y))
		game->player.speed.y = 0;
}
