/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:43:54 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:51:37 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	is_colliding(t_game *game, t_sprite *entity)
{
	t_vector3d	player_pos;
	t_vector3d	entity_pos;
	double		distance;

	while (entity)
	{
		player_pos = game->player.pos;
		entity_pos = entity->pos;
		distance = vec_distance(player_pos, entity_pos);
		if (distance < 50)
		{
			if (entity->type == ITEM)
			{
				if (is_consommable(entity))
					use_item(game, entity);
				else
					add_item(game, entity->id);
				remove_entity(&game->sprites, entity);
			}
			return ;
		}
		entity = entity->next;
	}
}

bool	is_colliding_entity(t_sprite *sprites, t_sprite *entity)
{
	t_vector3d	current_pos;
	t_vector3d	entity_pos;
	double		distance;

	entity_pos = entity->pos;
	while (sprites)
	{
		current_pos = sprites->pos;
		distance = vec_distance(current_pos, entity_pos);
		if (distance < entity->width / 2 && sprites != entity)
			return (true);
		sprites = sprites->next;
	}
	return (false);
}

bool	is_colliding_entity_dir(t_sprite *sprites, t_sprite *entity, char dir)
{
	t_vector3d	current_pos;
	bool		ret;

	current_pos = entity->pos;
	if (dir == 'N')
		entity->pos.y -= 1.5;
	else if (dir == 'S')
		entity->pos.y += 1.5;
	else if (dir == 'E')
		entity->pos.x += 1.5;
	else if (dir == 'W')
		entity->pos.x -= 1.5;
	ret = is_colliding_entity(sprites, entity);
	entity->pos = current_pos;
	return (ret);
}
