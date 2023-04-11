/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_zombie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 11:44:19 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_zombie_anim(t_game *game)
{
	fill_sprite_animation(game, "images/FPS_pixel_zombie/ATTACK_CROPPED_XPM", &game->animations.zombie_hit);
	game->animations.zombie_hit.frame_duration_ms = 15;
	fill_sprite_animation(game, "images/FPS_pixel_zombie/RUN_CROPPED_XPM", &game->animations.zombie_run);
	game->animations.zombie_run.frame_duration_ms = 30;
	fill_sprite_animation(game, "images/FPS_pixel_zombie/DEAD_CROPPED_XPM", &game->animations.zombie_death);
	game->animations.zombie_death.frame_duration_ms = 30;
	fill_sprite_animation(game, "images/FPS_pixel_zombie/SPAWN_CROPPED_XPM", &game->animations.zombie_spawn);
	game->animations.zombie_spawn.frame_duration_ms = 15;
}

t_sprite	*spawn_zombie(t_game *game, t_vector3d pos)
{
	t_sprite	*new_zombie;

	new_zombie = my_alloc(sizeof(t_sprite));
	if (!new_zombie)
		return (NULL);
	new_zombie->pos.x = pos.x;
	new_zombie->pos.y = pos.y;
	new_zombie->pos.z = pos.z;
	new_zombie->animation = game->animations.zombie_spawn;
	new_zombie->animation.start_time_ms = game->time.frame.tv_sec * 1000 +
		game->time.frame.tv_usec / 1000;
	new_zombie->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * new_zombie->animation.nb_imgs;
	new_zombie->height = 50;
	new_zombie->width = new_zombie->height *
		(new_zombie->animation.current_img->width) /
			(new_zombie->animation.current_img->heigth);
	new_zombie->speed.x = 0;
	new_zombie->speed.y = 0;
	new_zombie->speed.z = 0;
	new_zombie->type = MOB;
	new_zombie->velocity = 3;
	new_zombie->hp = 200;
	new_zombie->attacked = false;
	new_zombie->state = SPAWN;
	new_zombie->next = NULL;
	sprite_add_back(&game->sprites, new_zombie);
	return (new_zombie);
}
