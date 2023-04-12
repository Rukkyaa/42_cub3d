/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_zombie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/12 13:57:47 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_zombie_anim(t_game *game)
{
	fill_sprite_animation(game, "images/FPS_pixel_zombie/ATTACK_CROPPED_XPM", &game->animations.zombie_hit);
	game->animations.zombie_hit.frame_duration_ms = 15;
	fill_sprite_animation(game, "images/FPS_pixel_zombie/RUN_CROPPED_XPM", &game->animations.zombie_run);
	game->animations.zombie_run.frame_duration_ms = 30;
	fill_sprite_animation(game, "images/FPS_pixel_zombie/WALK_CROPPED_XPM", &game->animations.zombie_walk);
	game->animations.zombie_walk.frame_duration_ms = 30;
	fill_sprite_animation(game, "images/FPS_pixel_zombie/DEAD_CROPPED_XPM", &game->animations.zombie_death);
	game->animations.zombie_death.frame_duration_ms = 30;
	fill_sprite_animation(game, "images/FPS_pixel_zombie/SPAWN_CROPPED_XPM", &game->animations.zombie_spawn);
	game->animations.zombie_spawn.frame_duration_ms = 15;
}

t_sprite	*spawn_zombie(t_game *game, t_vector3d pos, int type)
{
	t_sprite	*new_zombie;

	new_zombie = my_alloc(sizeof(t_sprite));
	if (!new_zombie)
		return (NULL);
	new_zombie->pos.x = pos.x;
	new_zombie->pos.y = pos.y;
	new_zombie->pos.z = pos.z;
	new_zombie->animated_mob.spawn = game->animations.zombie_spawn;
	new_zombie->animated_mob.run = game->animations.zombie_run;
	new_zombie->animated_mob.hit = game->animations.zombie_hit;
	new_zombie->animated_mob.death = game->animations.zombie_death;
	new_zombie->animation = new_zombie->animated_mob.spawn;
	update_start_time(new_zombie, game);
	if (type == NORMAL_ZOMBIE)
	{
		new_zombie->height = 45;
		new_zombie->velocity = 4;
		new_zombie->hp = 200;
		new_zombie->damage = 10;
	}
	else if (type == BABY_ZOMBIE)
	{
		new_zombie->height = 30;
		new_zombie->velocity = 5;
		new_zombie->hp = 100;
		new_zombie->animated_mob.hit.frame_duration_ms = 10;
		new_zombie->damage = 5;
	}
	else if (type == BIG_ZOMBIE)
	{
		new_zombie->height = 60;
		new_zombie->velocity = 2;
		new_zombie->hp = 500;
		new_zombie->animated_mob.run = game->animations.zombie_walk;
		new_zombie->animated_mob.hit.frame_duration_ms = 20;
		new_zombie->damage = 50;
	}
	update_width(new_zombie);
	new_zombie->speed.x = 0;
	new_zombie->speed.y = 0;
	new_zombie->speed.z = 0;
	new_zombie->type = MOB;
	new_zombie->attacked = false;
	new_zombie->state = SPAWN;
	new_zombie->next = NULL;
	sprite_add_back(&game->sprites, new_zombie);
	return (new_zombie);
}
