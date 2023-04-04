/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/04 14:05:51 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	move_mob(t_sprite *sprite, t_player *player)
{
	if (vec_distance(sprite->pos, player->pos) < 30
		|| vec_distance(sprite->pos, player->pos) > 400)
		return ;
	sprite->speed = vec_sum(player->pos, vec_scalar_mult(sprite->pos, -1));
	sprite->speed = vec_normalize(sprite->speed);
	sprite->pos = vec_sum(vec_scalar_mult(sprite->speed, sprite->velocity), sprite->pos);
	sprite->pos.z = -5;
}

void	move_sprites(t_sprite *sprites, t_player *player)
{
	t_sprite	*begin;

	begin = sprites;
	while (sprites)
	{
		if (sprites->type == MOB)
			move_mob(sprites, player);
		sprites = sprites->next;
	}
}
