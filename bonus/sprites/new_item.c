/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:14 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 11:49:19 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_animation	load_item_anim(t_game *game, char *type)
{
	t_animation	anim;

	anim.nb_imgs = 1;
	anim.imgs = NULL;
	if (!strcmp(type, "sword"))
		anim.current_img = &game->weapon_icons.sword;
	else if (!strcmp(type, "axe"))
		anim.current_img = &game->weapon_icons.axe;
	else if (!strcmp(type, "heart"))
		anim.current_img = &game->texture.heart;
	anim.frame_duration_ms = 30;
	return (anim);
}

t_animation	get_item_anim(t_game *game, char *type)
{
	if (!strcmp(type, "sword"))
		return (game->animations.sword);
	else if (!strcmp(type, "axe"))
		return (game->animations.axe);
	else if (!strcmp(type, "heart"))
		return (game->animations.heart);
	return (game->animations.sword);
}

t_sprite	*spawn_item(t_game *game, t_vector3d pos, char *type)
{
	t_sprite	*new_item;

	new_item = my_alloc(sizeof(t_sprite));
	if (!new_item)
		return (NULL);
	new_item->pos.x = pos.x;
	new_item->pos.y = pos.y;
	new_item->animation = get_item_anim(game, type);
	new_item->animation.start_time_ms = game->time.frame.tv_sec * 1000 +
		game->time.frame.tv_usec / 1000;
	new_item->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * new_item->animation.nb_imgs;
	new_item->pos.z = 0;
	new_item->height = 20;
	new_item->width = new_item->height *
		(new_item->animation.current_img->width) /
			(new_item->animation.current_img->heigth);
	new_item->name = type;
	new_item->next = NULL;
	new_item->type = ITEM;
	sprite_add_back(&game->sprites, new_item);
	return (new_item);
}
