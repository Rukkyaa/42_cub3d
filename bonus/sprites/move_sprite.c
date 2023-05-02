/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/02 11:39:34 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	do_damage(int damage, t_sprite *sprite)
{
	sprite->hp -= damage;
	if (sprite->hp <= 0)
		return (true);
	return (false);
}

static void	move_mob(t_game *game, t_sprite *sprite, t_player *player)
{
	if (sprite->state == SPAWN)
		sprite_spawn(game, sprite);
	else if (sprite->hp <= 0 || sprite->state == DEATH)
		sprite_death(game, sprite);
	else if (vec_distance(sprite->pos, player->pos) < 30
		|| sprite->state == ATTACK)
		attack(game, sprite, player);
	else
	{
		sprite->speed = vec_sum(player->pos, vec_scalar_mult(sprite->pos, -1));
		sprite->speed = vec_normalize(sprite->speed);
		sprite->speed = vec_scalar_mult(sprite->speed, sprite->velocity);
		sprite->speed.z = 0;
		mob_wall_collide(game, sprite);
		check_mob_collisions(game, sprite);
		sprite->pos = vec_sum(sprite->pos, sprite->speed);
	}
}

static void	move_proj(t_game *game, t_sprite *proj, t_sprite **sprites)
{
	t_sprite	*tmp;

	tmp = *sprites;
	while (tmp)
	{
		if (tmp->type == PROJ)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type == MOB && proj_mob_collide(tmp, proj) && tmp->hp > 0)
		{
			if (do_damage(proj->damage + game->player.bonus_strength, tmp))
				update_kill(game);
			remove_entity(sprites, proj);
			return ;
		}
		tmp = tmp->next;
	}
	if (projectile_terrain_collide(game->map, proj))
		return (remove_entity(sprites, proj));
	proj->last_pos = proj->pos;
	proj->pos = vec_sum(proj->pos, proj->speed);
}

void	check_remove(t_game *game, t_sprite *fx, t_sprite **sprites)
{
	int	time_elapsed_ms;

	time_elapsed_ms = (game->time.frame.tv_sec * 1000 + game->time.frame.tv_usec
			/ 1000) - fx->animation.start_time_ms;
	if (time_elapsed_ms > fx->animation.frame_duration_ms
		* fx->animation.nb_imgs)
		remove_entity(sprites, fx);
}

void	move_sprites(t_game *game, t_sprite **sprites, t_player *player)
{
	t_sprite	*tmp;
	t_sprite	*tmp_prev;

	tmp = *sprites;
	tmp->prev = NULL;
	while (tmp)
	{
		if (tmp->type == MOB)
			move_mob(game, tmp, player);
		else if (tmp->type == PROJ)
			move_proj(game, tmp, sprites);
		else if (tmp->type == FX)
			check_remove(game, tmp, sprites);
		tmp_prev = tmp;
		tmp = tmp->next;
		if(tmp)
			tmp->prev = tmp_prev;
	}
}
