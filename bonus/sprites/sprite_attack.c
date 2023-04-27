/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_attack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:36:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/27 17:07:53 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	can_attack(t_sprite *sprite, t_player *player)
{
	return (sprite->animation.current_frame > 60
		&& sprite->animation.current_frame < 70 && sprite->attacked == false
		&& vec_distance(sprite->pos, player->pos) < 60);
}

void	update_width(t_sprite *sprite)
{
	sprite->width = sprite->height * (sprite->animation.current_img->width)
		/ (sprite->animation.current_img->heigth);
}

void	update_start_time(t_sprite *sprite, t_game *game)
{
	sprite->animation.start_time_ms = game->time.frame.tv_sec * 1000
		+ game->time.frame.tv_usec / 1000;
}

void	attack(t_game *game, t_sprite *sprite, t_player *player)
{
	if ((!sprite->state) == ATTACK)
	{
		sprite->state = ATTACK;
		sprite->animation = sprite->animated_mob.hit;
		update_start_time(sprite, game);
		update_width(sprite);
	}
	if (can_attack(sprite, player))
	{
		sprite->attacked = true;
		player->hp -= sprite->damage;
		player->sound_state.player_hurt = true;
		if (player->hp <= 0)
		{
			if(game->player.real_death_time == 0)
				game->player.real_death_time = game->frame_count;
			if (game->player.lethal_hits == 0)
				printf("You died, %d\n", player->kills);
			if(game->player.lethal_hits < 2)
			{
				game->player.death_time = game->frame_count;
				game->player.lethal_hits++;
			}
		}
	}
	else if (sprite->animation.current_frame > 70)
		sprite->attacked = false;
	if (sprite->animation.current_frame > 110
		&& vec_distance(sprite->pos, player->pos) > 30)
	{
		sprite->state = RUN;
		sprite->animation =  sprite->animated_mob.run;
		update_start_time(sprite, game);
		update_width(sprite);
		sprite->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * sprite->animation.nb_imgs;
	}
}
