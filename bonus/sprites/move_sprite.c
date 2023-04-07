/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 15:10:20 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	can_move(char **map, t_vector3d pos)
{
	int	x;
	int	y;

	x = (int)(pos.x) / 64;
	y = (int)(pos.y) / 64;
	if (is_wall(map[y][x]) || ((pos.z < 0 || 64 < pos.z) && pos.z != -5))
		return (false);
	return (true);
}

static bool	do_damage(t_sprite *proj, t_sprite *sprite)
{
	sprite->hp -= 100;
	if (sprite->hp <= 0)
		return (true);
	return (false);
}

static void	move_mob(t_game *game, t_sprite *sprite, t_player *player)
{
	t_vector3d	tmp;
	t_vector3d	start;

	if (sprite->state == SPAWN)
	{
		if (sprite->animation.current_frame > 160)
		{
			sprite->state = RUN;
			sprite->animation = game->animations.zombie_run;
			update_start_time(sprite, game);
			update_width(sprite);
		}
		return ;
	}
	else if (sprite->hp <= 0 || sprite->state == DEATH)
	{
		if (sprite->state != DEATH)
		{
			sprite->state = DEATH;
			sprite->animation = game->animations.zombie_death;
			update_start_time(sprite, game);
			update_width(sprite);
		}
		if (sprite->animation.current_frame > 40)
		{
			// spawn_item(game, sprite->pos, "axe");
			remove_entity(&game->sprites, sprite);
		}
	}
	else if (vec_distance(sprite->pos, player->pos) < 30 || sprite->state == ATTACK)
	{
		attack(game, sprite, player);
		return ;
	}
	else
	{
		start = sprite->speed;
		sprite->speed = vec_sum(player->pos, vec_scalar_mult(sprite->pos, -1));
		sprite->speed = vec_normalize(sprite->speed);
		tmp = vec_sum(vec_scalar_mult(sprite->speed, sprite->velocity),
				sprite->pos);
		if (can_move(game->map, tmp))
			sprite->pos = tmp;
		sprite->pos.z = -5;
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
		if (vec_distance(proj->pos, tmp->pos) < (proj->width / 2)
			&& tmp->type == MOB && proj->pos.z < tmp->pos.z + tmp->height && tmp->hp > 0)
		{
			if (do_damage(proj, tmp))
				game->player.kills++;
			remove_entity(sprites, proj);
			return ;
		}
		tmp = tmp->next;
	}
	if (can_move(game->map, vec_sum(proj->pos, proj->speed)))
		proj->pos = vec_sum(proj->pos, proj->speed);
	else
		remove_entity(sprites, proj);
}

void	move_sprites(t_game *game, t_sprite **sprites, t_player *player)
{
	t_sprite	*tmp;

	tmp = *sprites;
	while (tmp)
	{
		if (tmp->type == MOB)
			move_mob(game, tmp, player);
		else if (tmp->type == PROJ)
			move_proj(game, tmp, sprites);
		tmp = tmp->next;
	}
}
