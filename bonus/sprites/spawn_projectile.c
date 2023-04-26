/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:49:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/25 17:20:05 by teliet           ###   ########.fr       */
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
	return (anim);
}

void	set_type_specs(t_sprite *new_proj, int type)
{
	if (type == GREEN_PROJ)
	{
		new_proj->damage = 50;
		new_proj->height = 32;
	}
	else if (type == BLUE_PROJ)
	{
		new_proj->damage = 25;
		new_proj->height = 16;
	}
}

t_sprite	*spawn_projectile(t_game *game, t_vector3d pos, int type)
{
	t_sprite	*new_proj;

	new_proj = my_alloc(sizeof(t_sprite));
	if (!new_proj)
		return (NULL);
	new_proj->pos.x = pos.x + game->player.direction.x * 10;
	new_proj->pos.y = pos.y + game->player.direction.y * 10;
	new_proj->animation = get_energy_ball_anim(game, type);
	new_proj->animation.frame_offset = ((double)rand() / (double)RAND_MAX)
		* new_proj->animation.nb_imgs;
	new_proj->pos.z = 20 - new_proj->height / 2;
	new_proj->last_pos = new_proj->pos;
	new_proj->speed = game->player.direction;
	new_proj->speed.z = (float)1.25 * (game->camera.plane_center.y
			- game->camera.half_res.y) / (float)game->camera.p_plane_dist;
	new_proj->speed = vec_scalar_mult(new_proj->speed, 25);
	new_proj->next = NULL;
	new_proj->type = PROJ;
	set_type_specs(new_proj, type);
	new_proj->width = new_proj->height
		* (new_proj->animation.current_img->width)
		/ (new_proj->animation.current_img->heigth);
	sprite_add_back(&game->sprites, new_proj);
	return (new_proj);
}
