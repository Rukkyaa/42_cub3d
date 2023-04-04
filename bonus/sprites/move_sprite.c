/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/04 15:08:58 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	do_damage(t_sprite *proj, t_sprite *sprite)
{
	sprite->hp -= 100;
	if (sprite->hp <= 0)
		return (true);
	return (false);
}

static void	move_mob(t_sprite *sprite, t_player *player)
{
	if (vec_distance(sprite->pos, player->pos) < 30
		|| vec_distance(sprite->pos, player->pos) > 400)
		return ;
	sprite->speed = vec_sum(player->pos, vec_scalar_mult(sprite->pos, -1));
	sprite->speed = vec_normalize(sprite->speed);
	sprite->pos = vec_sum(vec_scalar_mult(sprite->speed, sprite->velocity), sprite->pos);
	sprite->pos.z = -5;
}

static void	move_proj(t_sprite *proj, t_sprite **sprites)
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
    proj->pos = vec_sum(proj->pos, proj->speed);
}

void	move_sprites(t_sprite **sprites, t_player *player)
{
	t_sprite	*tmp;

	tmp = *sprites;
	while (tmp)
	{
		if (tmp->type == MOB)
			move_mob(tmp, player);
		else if (tmp->type == PROJ)
			move_proj(tmp, sprites);
		tmp = tmp->next;
	}
}
