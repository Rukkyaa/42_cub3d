/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_zombie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/06 18:43:33 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_animation	get_zombie_anim(t_game *game)
{
	t_animation	anim;

	anim.nb_imgs = 30;
	// anim.imgs = fill_sprite_animation(game, "images/FPS_pixel_zombie/RUN_CROPPED_XPM");
	anim.imgs = fill_sprite_animation(game, "images/MOBS/MANCUBUS/IDLE");
	anim.current_img = anim.imgs[0];
	anim.frame_duration_ms = 30;
	return (anim);
}

t_sprite	*spawn_zombie(t_game *game, t_vector pos)
{
	t_sprite	*new_zombie;

	new_zombie = my_alloc(sizeof(t_sprite));
	if (!new_zombie)
		return (NULL);
	new_zombie->pos.x = pos.x;
	new_zombie->pos.y = pos.y;
	new_zombie->pos.z = 0;
	new_zombie->animation = game->animations.zombie_run;
	new_zombie->animation.start_time_ms = game->time.frame.tv_sec * 1000 +
		game->time.frame.tv_usec / 1000;
	new_zombie->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * new_zombie->animation.nb_imgs;
	new_zombie->height = 54;
	new_zombie->width = new_zombie->height *
		(new_zombie->animation.current_img->width) /
			(new_zombie->animation.current_img->heigth);
	new_zombie->speed.x = 0;
	new_zombie->speed.y = 0;
	new_zombie->speed.z = 0;
	new_zombie->type = MOB;
	new_zombie->velocity = 3;
	new_zombie->hp = 200;
	new_zombie->next = NULL;
	sprite_add_back(&game->sprites, new_zombie);
	return (new_zombie);
}
