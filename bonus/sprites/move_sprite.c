/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/04 16:41:46 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	can_move(char **map, t_vector3d pos)
{
	int x;
	int y;

	x = (int)(pos.x) / 64;
	y = (int)(pos.y) / 64;
	if (is_wall(map[y][x]) || pos.z < 0 || 64 < pos.z)
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

static void	move_mob(char **map, t_sprite *sprite, t_player *player)
{
	t_vector3d	tmp;

	if (vec_distance(sprite->pos, player->pos) < 30
		|| vec_distance(sprite->pos, player->pos) > 400)
		return ;
	sprite->speed = vec_sum(player->pos, vec_scalar_mult(sprite->pos, -1));
	sprite->speed = vec_normalize(sprite->speed);
	tmp = vec_sum(vec_scalar_mult(sprite->speed, sprite->velocity), sprite->pos);
	if (can_move(map, tmp))
		sprite->pos = tmp;
	sprite->pos.z = -5;
}

static void	move_proj(char **map, t_sprite *proj, t_sprite **sprites)
{
	t_sprite *tmp;

	tmp = *sprites;
	while (tmp)
	{
		if (tmp->type == PROJ)
		{
			tmp = tmp->next;
			continue ;
		}
		if (vec_distance(proj->pos, tmp->pos) < 
			(proj->width / 2 + tmp->width / 2) && tmp->type == MOB)
		{
			if (do_damage(proj, tmp))
				remove_entity(sprites, tmp);
			remove_entity(sprites, proj);
			return ;
		}
		tmp = tmp->next;
	}
	if (can_move(map, vec_sum(proj->pos, proj->speed)))
    	proj->pos = vec_sum(proj->pos, proj->speed);
	else
		remove_entity(sprites, proj);
}

void	move_sprites(char **map, t_sprite **sprites, t_player *player)
{
	t_sprite	*tmp;

	tmp = *sprites;
	while (tmp)
	{
		if (tmp->type == MOB)
			move_mob(map, tmp, player);
		else if (tmp->type == PROJ)
			move_proj(map, tmp, sprites);
		tmp = tmp->next;
	}
}
