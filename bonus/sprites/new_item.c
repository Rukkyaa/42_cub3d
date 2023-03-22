/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/22 15:25:31 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_sprite	*spawn_item(t_game *game, t_animation anim, t_vector pos)
{
	t_sprite	*item;

	item = malloc(sizeof(t_sprite));
	if (!item)
		return (NULL);
	item->pos.x = pos.x;
	item->pos.y = pos.y;
	item->animation = anim;
	item->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * anim.nb_imgs;
	item->pos.z = 0;
	item->height = 10;
	item->width = item->height *
		(item->animation.current_img->width) /
			(item->animation.current_img->heigth);
	// item->speed.x = 0.1;
	// item->speed.y = 0.1;
	// item->type = "zombie";
	item->next = NULL;
	sprite_add_back(&game->sprites, item);
	return (item);
}
