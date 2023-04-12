/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_attack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:36:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/12 12:43:42 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	can_attack(t_sprite *sprite, t_player *player)
{
	return (sprite->animation.current_frame > 60
		&& sprite->animation.current_frame < 70 && sprite->attacked == false
		&& vec_distance(sprite->pos, player->pos) < 45);
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
		player->hp -= 10;
	}
	else if (sprite->animation.current_frame > 70)
		sprite->attacked = false;
	if (sprite->animation.current_frame > 110
		&& vec_distance(sprite->pos, player->pos) > 30)
	{
		sprite->state = RUN;
		sprite->animation =  sprite->animated_mob.run;
		update_width(sprite);
	}
}
