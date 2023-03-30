/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:57:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/03/31 00:03:05 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Function to remove an entity from the linked list of entities
** It takes the game struct and the entity to remove as parameters
**
** @param game the game struct
** @param entity the entity to remove
*/
void	remove_entity(t_game *game, t_sprite *entity)
{
	t_sprite	*tmp;

	tmp = game->sprites;
	if (tmp == entity)
	{
		game->sprites = tmp->next;
		return ;
	}
	while (tmp->next != entity)
		tmp = tmp->next;
	tmp->next = entity->next;
}


// void	remove_entity(t_game *game, int id)
// {
// 	t_sprite	*entity;
// 	t_sprite	*prev;

// 	entity = game->sprites;
// 	prev = NULL;
// 	while (entity)
// 	{
// 		if (entity->id == id)
// 		{
// 			if (prev)
// 				prev->next = entity->next;
// 			else
// 				game->sprites = entity->next;
// 			free(entity);
// 			return ;
// 		}
// 		prev = entity;
// 		entity = entity->next;
// 	}
// }
