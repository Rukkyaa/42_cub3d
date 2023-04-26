/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/26 12:24:49 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_camera(t_game *game, t_camera *camera)
{
	camera->proj_plane_height = RES_Y;
	camera->proj_plane_width = RES_X;
	camera->half_res.x = RES_X / 2;
	camera->half_res.y = RES_Y / 2;
	camera->p_plane_dist = ((float)camera->proj_plane_width / 2.0f)
		/ tanf(FOV_RADIANS / 2.0f);
	camera->plane.x = 0;
	camera->plane.y = camera->proj_plane_width / 2;
	camera->plane.z = 0;
	camera->plane_center.x = camera->half_res.x;
	camera->plane_center.y = camera->half_res.y;
	game->wall_height_x_proj_dist = game->wall_height
		* game->camera.p_plane_dist;
}
