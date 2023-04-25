/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:29:41 by teliet            #+#    #+#             */
/*   Updated: 2023/04/25 17:47:15 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	pre_compute_resize(t_game *game)
{
	int			i;
	t_vector3d	v_right;
	t_vector3d	v_ray_dir;
	t_vector3d	v_player_to_camera_plane;
	float		ca;

	i = 0;
	v_right = vec_rotate(game->player.direction, 90);
	v_player_to_camera_plane = vec_scalar_mult(game->player.direction,
			game->camera.p_plane_dist);
	while (i < RES_X)
	{
		v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right,
					game->ray_offset[i]));
		ca = vec_angle(v_ray_dir, game->player.direction);
		game->fisheye_resize[i] = cosf(ca);
		game->fisheye_resize_wall[i] = cosf(ca);
		i++;
	}
}
