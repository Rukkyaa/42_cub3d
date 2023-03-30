/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:43:54 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/03/30 23:57:14 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Function to check if the player is colliding with an entity by checking with the entity's hitbox (a circle)
int		is_colliding(t_game *game, t_sprite *entity)
{
	t_vector3d		player_pos;
	t_vector3d		entity_pos;
	double			distance;

	//loop on all entities
	while (entity)
	{
		player_pos = game->player.pos;
		entity_pos = entity->pos;
		distance = vec_distance(player_pos, entity_pos);
		if (distance < 50)
		{
			return (1);
		}
		entity = entity->next;
	}
	return (0);
}
