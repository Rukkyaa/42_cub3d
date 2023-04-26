/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:57:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/04/04 14:44:44 by axlamber         ###   ########.fr       */
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
void	remove_entity(t_sprite **sprites, t_sprite *entity)
{
	t_sprite	*tmp;

	if (*sprites == entity)
	{
		*sprites = (*sprites)->next;
		return ;
	}
	tmp = *sprites;
	while (tmp && tmp->next != entity)
		tmp = tmp->next;
	if (tmp)
		tmp->next = entity->next;
}
