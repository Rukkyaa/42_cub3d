/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/12 17:31:28 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_animation	get_energy_ball_anim(t_game *game, int type)
{
	t_animation	anim;

	anim.nb_imgs = 1;
	anim.imgs = NULL;
	if (type == GREEN_PROJ)
		anim.current_img = &game->texture.projectile;
	else if (type == BLUE_PROJ)
		anim.current_img = &game->texture.blue_projectile;
	anim.frame_duration_ms = 100000;
	// anim.play = 0;
	return (anim);
}

t_sprite	*spawn_projectile(t_game *game, t_vector3d pos, int type)
{
	t_sprite	*new_projectile;

	new_projectile = my_alloc(sizeof(t_sprite));
	if (!new_projectile)
		return (NULL);
	new_projectile->pos.x = pos.x + game->player.direction.x * 10;
	new_projectile->pos.y = pos.y + game->player.direction.y * 10;
	new_projectile->animation = get_energy_ball_anim(game, type);
	new_projectile->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * new_projectile->animation.nb_imgs;
	new_projectile->height = 32;
	new_projectile->pos.z = 20 - new_projectile->height / 2;
	new_projectile->last_pos = new_projectile->pos;
	new_projectile->width = new_projectile->height *
		(new_projectile->animation.current_img->width) /
			(new_projectile->animation.current_img->heigth);
	new_projectile->speed = game->player.direction;
	new_projectile->speed.z = (float) 1.25 * (game->camera.plane_center.y -  game->camera.half_res.y) / (float) game->camera.proj_plane_distance;
	new_projectile->speed = vec_scalar_mult(new_projectile->speed, 25);
	new_projectile->next = NULL;
	new_projectile->type = PROJ;
	sprite_add_back(&game->sprites, new_projectile);
	return (new_projectile);
}
