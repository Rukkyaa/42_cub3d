/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/04 14:01:38 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_sprites(t_sprite *sprites, t_player *player)
{
	t_sprite	*begin;

	begin = sprites;
	while (sprites)
	{
		if (sprites->type != MOB || vec_distance(sprites->pos, player->pos)
			< 30 || vec_distance(sprites->pos, player->pos) > 400)
		{
			sprites = sprites->next;
			continue;
		}
		sprites->speed = vec_sum(player->pos, vec_scalar_mult(sprites->pos, -1));
		sprites->speed = vec_normalize(sprites->speed);
		sprites->pos = vec_sum(vec_scalar_mult(sprites->speed, sprites->velocity), sprites->pos);
		sprites->pos.z = -5;
		sprites = sprites->next;
	}
}
