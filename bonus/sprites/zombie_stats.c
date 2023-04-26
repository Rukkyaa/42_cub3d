/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_zombie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/21 15:38:37 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_baby_zombie_stats(t_sprite *zombie, t_wave *wave)
{
	zombie->velocity = wave->baby_zombie_stats.velocity;
	zombie->hp = wave->baby_zombie_stats.hp;
	zombie->damage = wave->baby_zombie_stats.damage;
	zombie->range = wave->baby_zombie_stats.range;
	zombie->height = 30;
}

void	set_normal_zombie_stats(t_sprite *zombie, t_wave *wave)
{
	zombie->velocity = wave->normal_zombie_stats.velocity;
	zombie->hp = wave->normal_zombie_stats.hp;
	zombie->damage = wave->normal_zombie_stats.damage;
	zombie->range = wave->normal_zombie_stats.range;
	zombie->height = 45;
}

void	set_big_zombie_stats(t_sprite *zombie, t_wave *wave)
{
	zombie->velocity = wave->big_zombie_stats.velocity;
	zombie->hp = wave->big_zombie_stats.hp;
	zombie->damage = wave->big_zombie_stats.damage;
	zombie->range = wave->big_zombie_stats.range;
	zombie->height = 60;
}

void	set_type_specs_zomb(t_game *game, t_sprite *new_zombie, int type)
{
	if (type == NORMAL_ZOMBIE)
		set_normal_zombie_stats(new_zombie, game->current_wave);
	else if (type == BABY_ZOMBIE)
	{
		set_baby_zombie_stats(new_zombie, game->current_wave);
		new_zombie->animated_mob.hit.frame_duration_ms = 5;
	}
	else if (type == BIG_ZOMBIE)
	{
		set_big_zombie_stats(new_zombie, game->current_wave);
		new_zombie->animated_mob.run = game->animations.zombie_walk;
		new_zombie->animated_mob.hit.frame_duration_ms = 15;
	}
}
