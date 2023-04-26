/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/12 17:58:26 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_blood_anim(t_game *game)
{
	fill_sprite_animation(game, "images/FX/blood_splatter_line_xpm",
		&game->animations.blood_splatter_line);
	game->animations.blood_splatter_line.frame_duration_ms = 70;
}

t_sprite	*spawn_blood(t_game *game, t_vector3d pos, int type)
{
	t_sprite	*new_blood;

	new_blood = my_alloc(sizeof(t_sprite));
	if (!new_blood)
		return (NULL);
	new_blood->pos.x = pos.x;
	new_blood->pos.y = pos.y;
	new_blood->pos.z = 16;
	new_blood->animation = game->animations.blood_splatter_line;
	new_blood->animation.frame_offset = 0;
	new_blood->last_pos = new_blood->pos;
	new_blood->speed.x = 0;
	new_blood->speed.y = 0;
	new_blood->speed.z = 0;
	new_blood->next = NULL;
	new_blood->type = FX;
	new_blood->height = 10;
	new_blood->width = new_blood->height
		* (new_blood->animation.current_img->width)
		/ (new_blood->animation.current_img->heigth);
	sprite_add_back(&game->sprites, new_blood);
	update_start_time(new_blood, game);
	return (new_blood);
}
