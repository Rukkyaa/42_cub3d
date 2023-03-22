/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_zombie.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/22 15:04:00 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_sprite	*spawn_zombie(t_game *game, t_animation anim, t_vector pos)
{
	t_sprite	*new_zombie;

	new_zombie = malloc(sizeof(t_sprite));
	if (!new_zombie)
		return (NULL);
	new_zombie->pos.x = pos.x;
	new_zombie->pos.y = pos.y;
	new_zombie->animation = anim;
	new_zombie->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * anim.nb_imgs;
	new_zombie->pos.z = -5;
	new_zombie->height = 70;
	new_zombie->width = new_zombie->height *
		(new_zombie->animation.current_img->width) /
			(new_zombie->animation.current_img->heigth);
	// new_zombie->speed.x = 0.1;
	// new_zombie->speed.y = 0.1;
	// new_zombie->type = "zombie";
	new_zombie->next = NULL;
	sprite_add_back(&game->sprites, new_zombie);
	return (new_zombie);
}
