/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/23 13:18:50 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_animation	get_energy_ball_anim(t_game *game)
{
	t_animation	anim;

	anim.nb_imgs = 1;
	anim.imgs = NULL;
	anim.current_img = &game->texture.projectile;
	anim.frame_duration_ms = 100000;
	// anim.play = 0;
	return (anim);
}

t_sprite	*spawn_projectile(t_game *game, t_vector3d pos, t_vector3d speed)
{
	t_sprite	*new_projectile;

	new_projectile = malloc(sizeof(t_sprite));
	if (!new_projectile)
		return (NULL);
	new_projectile->pos.x = game->player.pos.x;
	new_projectile->pos.y = game->player.pos.y;
	new_projectile->animation = get_energy_ball_anim(game);
	new_projectile->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * new_projectile->animation.nb_imgs;
	new_projectile->pos.z = 40;
	new_projectile->height = 32;
	new_projectile->width = new_projectile->height *
		(new_projectile->animation.current_img->width) /
			(new_projectile->animation.current_img->heigth);
	new_projectile->speed = speed;
	// new_projectile->type = "zombie";
	new_projectile->next = NULL;
	new_projectile->type = PROJ;
	sprite_add_back(&game->sprites, new_projectile);
	return (new_projectile);
}
