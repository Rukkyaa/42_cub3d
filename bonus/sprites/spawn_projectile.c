/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 17:08:44 by teliet           ###   ########.fr       */
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

t_sprite	*spawn_projectile(t_game *game, t_vector3d pos)
{
	t_sprite	*new_projectile;

	new_projectile = my_alloc(sizeof(t_sprite));
	if (!new_projectile)
		return (NULL);
	new_projectile->pos.x = pos.x + game->player.direction.x * 30;
	new_projectile->pos.y = pos.y + game->player.direction.y * 30;
	new_projectile->animation = get_energy_ball_anim(game);
	new_projectile->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * new_projectile->animation.nb_imgs;
	new_projectile->pos.z = 5;
	new_projectile->height = 32;
	new_projectile->width = new_projectile->height *
		(new_projectile->animation.current_img->width) /
			(new_projectile->animation.current_img->heigth);
	new_projectile->speed = game->player.direction;//	vec_scalar_mult(game->player.direction, 1);
	new_projectile->speed.z = (float) 1.25 * (game->camera.plane_center.y -  game->camera.half_res.y) / (float) game->camera.proj_plane_distance;
	// printf("new_projectile->speed.z %f\n", new_projectile->speed.z);
	// printf("half_res %f\n", game->camera.half_res.y);
	// printf("plane_center %f\n",game->camera.plane_center.y);
	// printf("proj_plane_distance %f\n", game->camera.proj_plane_distance);
	// printf("z %f\n", ( game->camera.half_res.y - game->camera.plane_center.y) / game->camera.proj_plane_distance);
	// vec3_print(new_projectile->speed, "proj speed");
	new_projectile->speed = vec_scalar_mult(new_projectile->speed, 25);
	// vec3_print(new_projectile->speed, "proj speed");
	// new_projectile->type = "zombie";
	new_projectile->next = NULL;
	new_projectile->type = PROJ;
	sprite_add_back(&game->sprites, new_projectile);
	return (new_projectile);
}
