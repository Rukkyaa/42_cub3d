/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:49:22 by teliet            #+#    #+#             */
/*   Updated: 2023/05/03 11:31:13 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sprite_spawn(t_game *game, t_sprite *sprite)
{
	if (sprite->animation.current_frame > 160)
	{
		sprite->state = RUN;
		sprite->animation = sprite->animated_mob.run;
		update_start_time(sprite, game);
		update_width(sprite);
		sprite->animation.frame_offset = ((double)rand() / (double)RAND_MAX)
			* sprite->animation.nb_imgs;
	}
}

void	drop_item(t_game *game, t_sprite *sprite)
{
	float	rand_num;

	rand_num = (float)((double)rand() / (double)RAND_MAX);
	if (rand_num <= 0.10)
		spawn_item(game, sprite->pos, HEALTH);
	else if (rand_num > 0.10 && rand_num <= 0.25
		&& !weapon_in_inventory(game, GRAP_GUN))
		spawn_item(game, sprite->pos, GRAP_GUN);
	else if (rand_num > 0.25 && rand_num <= 0.40
		&& !weapon_in_inventory(game, PLASMA_RIFFLE))
		spawn_item(game, sprite->pos, PLASMA_RIFFLE);
	else if (rand_num > 0.40 && rand_num <= 0.45 && !game->player.cocaine)
		spawn_item(game, sprite->pos, COCAINE);
	else if (rand_num > 0.45 && rand_num <= 0.50
		&& !weapon_in_inventory(game, SHOTGUN))
		spawn_item(game, sprite->pos, SHOTGUN);
}

void	sprite_death(t_game *game, t_sprite *sprite)
{
	if (sprite->state != DEATH)
	{
		sprite->state = DEATH;
		sprite->animation = sprite->animated_mob.death;
		update_start_time(sprite, game);
		update_width(sprite);
	}
	if (sprite->animation.current_frame > 40)
	{
		drop_item(game, sprite);
		remove_entity(&game->sprites, sprite);
	}
}
