/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:31:21 by teliet            #+#    #+#             */
/*   Updated: 2023/05/02 15:00:24 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	projectile_terrain_collide(char **map, t_sprite *proj)
{
	int	x;
	int	y;

	x = (int)(proj->pos.x + proj->speed.x) / 64;
	y = (int)(proj->pos.y + proj->speed.y) / 64;
	if (is_wall(map[y][x]) || ((proj->pos.z + proj->speed.z + proj->height
				/ 2 < 0 || 64 < proj->pos.z + proj->speed.z + proj->height
				/ 2)))
		return (true);
	return (false);
}

void	mob_wall_collide(t_game *game, t_sprite *mob)
{
	t_vector3d	v_offset;
	t_vector3d	vi_pos;
	t_vector3d	vi_pos_add_offset;

	v_offset.x = 0;
	v_offset.y = 0;
	if (mob->speed.x > 0)
		v_offset.x = mob->width / 2;
	else
		v_offset.x = -mob->width / 2;
	if (mob->speed.y > 0)
		v_offset.y = mob->width / 2;
	else
		v_offset.y = -mob->width / 2;
	vi_pos = pixel_to_tile(mob->pos);
	vi_pos_add_offset = pixel_to_tile(vec_sum(mob->pos, v_offset));
	if (!is_walkable(game, vi_pos_add_offset.x, vi_pos.y))
		mob->speed.x = 0;
	if (!is_walkable(game, vi_pos.x, vi_pos_add_offset.y))
		mob->speed.y = 0;
}

void	mob_mob_collide(t_sprite *sprite_a, t_sprite *sprite_b)
{
	t_vector3d	next_pos_a;
	t_vector3d	next_pos_b;
	float		distance;

	next_pos_a = vec_sum(sprite_a->pos, sprite_a->speed);
	next_pos_b = vec_sum(sprite_b->pos, sprite_b->speed);
	distance = vec_distance(next_pos_a, next_pos_b);
	if (distance < 10)
	{
		sprite_a->speed.x = 0;
		sprite_b->speed.x = 0;
		sprite_a->speed.y = 0;
		sprite_b->speed.y = 0;
	}
}

void	check_mob_collisions(t_sprite *sprite)
{
	t_sprite	*tmp;

	tmp = sprite->next;
	while (tmp)
	{
		if (tmp->type == MOB && tmp->state != SPAWN && tmp->state != DEATH)
			mob_mob_collide(sprite, tmp);
		tmp = tmp->next;
	}
}

int	proj_mob_collide(t_sprite *mob, t_sprite *proj)
{
	t_vector3d	proj_true_pos;
	float		straight_dist;

	straight_dist = sqrt((mob->pos.x - proj->pos.x) * (mob->pos.x - proj->pos.x)
			+ (mob->pos.y - proj->pos.y) * (mob->pos.y - proj->pos.y));
	if (straight_dist > sqrt((mob->collide_width / 2 + proj->width / 2)
			* (mob->collide_width / 2 + proj->width / 2)))
		return (0);
	proj_true_pos = proj->pos;
	proj_true_pos.z = proj_true_pos.z + proj->width / 2;
	if (proj_true_pos.z > mob->pos.z + mob->height)
		return (0);
	return (1);
}
