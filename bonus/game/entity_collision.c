/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:43:54 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/04/04 14:45:08 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Function to check if the player is colliding with an entity by checking with the entity's hitbox (a circle)
void	is_colliding(t_game *game, t_sprite *entity)
{
	t_vector3d		player_pos;
	t_vector3d		entity_pos;
	double			distance;

	while (entity)
	{
		player_pos = game->player.pos;
		entity_pos = entity->pos;
		distance = vec_distance(player_pos, entity_pos);
		if (distance < 50)
		{
			if (entity->type == 1)
			{
				add_item(game, entity->name);
				remove_entity(&game->sprites, entity);
			}
			return ;
		}
		entity = entity->next;
	}
}

// Function to check if an entity is colliding with another entity by checking with the entity's hitbox (a circle)
bool	is_colliding_entity(t_sprite *sprites, t_sprite *entity)
{
	t_vector3d		current_pos;
	t_vector3d		entity_pos;
	double			distance;

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

//Function to check if an entity is colliding in a specific direction with another entity by checking with the entity's hitbox (a circle)
bool	is_colliding_entity_dir(t_sprite *sprites, t_sprite *entity, char dir)
{
	t_vector3d		current_pos;
	bool			ret;

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
	// printf("%d\n", ret);
	return (ret);
}
