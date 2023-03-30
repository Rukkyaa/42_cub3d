/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:57:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/03/30 23:58:23 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//Function to remove an entity from the linked list by an id
void	remove_entity(t_game *game, int id)
{
	t_sprite	*entity;
	t_sprite	*prev;

	entity = game->sprites;
	prev = NULL;
	while (entity)
	{
		if (entity->id == id)
		{
			if (prev)
				prev->next = entity->next;
			else
				game->sprites = entity->next;
			free(entity);
			return ;
		}
		prev = entity;
		entity = entity->next;
	}
}
