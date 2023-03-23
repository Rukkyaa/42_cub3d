/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:14 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/23 14:38:13 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_animation	get_item_anim(t_game *game)
{
	t_animation	anim;

	anim.nb_imgs = 1;
	anim.imgs = NULL;
	anim.current_img = &game->weapon.sword;
	anim.frame_duration_ms = 30;
	return (anim);
}

t_sprite	*spawn_item(t_game *game, t_vector pos)
{
	t_sprite	*new_item;

	new_item = malloc(sizeof(t_sprite));
	if (!new_item)
		return (NULL);
	new_item->pos.x = pos.x;
	new_item->pos.y = pos.y;
	new_item->animation = game->animations.sword;
	new_item->animation.start_time_ms = game->time.frame.tv_sec * 1000 +
		game->time.frame.tv_usec / 1000;
	new_item->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * new_item->animation.nb_imgs;
	new_item->pos.z = 0;
	new_item->height = 20;
	new_item->width = new_item->height *
		(new_item->animation.current_img->width) /
			(new_item->animation.current_img->heigth);
	// new_item->speed.x = 0.1;
	// new_item->speed.y = 0.1;
	// new_item->type = "item";
	new_item->next = NULL;
	new_item->type = ITEM;
	sprite_add_back(&game->sprites, new_item);
	return (new_item);
}
