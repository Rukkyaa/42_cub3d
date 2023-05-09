/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:09:49 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/09 10:24:48 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_collision	fill_collision(t_vector point, float distance, char orientation,
		int x_pos_tex)
{
	t_collision	collision;

	collision.point = point;
	collision.distance = distance;
	collision.orientation = orientation;
	collision.x_pos_tex = x_pos_tex;
	return (collision);
}

t_collision	cast_2d_ray(t_game *game, t_vector direction)
{
	t_vector	v_ray_dir;
	t_vector	v_step;
	t_vector	v_ray_length_1d;
	t_vector	v_map_check;
	t_vector	collision_point;
	char		last_step;
	int			i;
	t_vector	v_ray_unit_step;
	int			tile_found;
	float		distance;

	v_ray_dir = direction;
	v_map_check = pixel_to_tile(game->player.pos);
	i = 0;
	v_ray_unit_step.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x) * (v_ray_dir.y
				/ v_ray_dir.x));
	v_ray_unit_step.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y) * (v_ray_dir.x
				/ v_ray_dir.y));
	if (v_ray_dir.x < 0)
	{
		v_step.x = -1;
		v_ray_length_1d.x = (game->player.pos.x - tile_to_pixel(v_map_check).x)
			/ 64 * v_ray_unit_step.x;
	}
	else
	{
		v_step.x = 1;
		v_ray_length_1d.x = (tile_to_pixel(v_map_check).x + 64
				- game->player.pos.x) / 64 * v_ray_unit_step.x;
	}
	if (v_ray_dir.y < 0)
	{
		v_step.y = -1;
		v_ray_length_1d.y = (game->player.pos.y - tile_to_pixel(v_map_check).y)
			/ 64 * v_ray_unit_step.y;
	}
	else
	{
		v_step.y = 1;
		v_ray_length_1d.y = (tile_to_pixel(v_map_check).y + 64
				- game->player.pos.y) / 64 * v_ray_unit_step.y;
	}
	tile_found = 0;
	distance = 0.0f;
	while (!tile_found)
	{
		if (v_ray_length_1d.x < v_ray_length_1d.y)
		{
			last_step = 'x';
			v_map_check.x += v_step.x;
			distance = v_ray_length_1d.x;
			v_ray_length_1d.x += v_ray_unit_step.x;
		}
		else
		{
			last_step = 'y';
			v_map_check.y += v_step.y;
			distance = v_ray_length_1d.y;
			v_ray_length_1d.y += v_ray_unit_step.y;
		}
		collision_point = vec_scalar_mult(v_ray_dir, distance * 64);
		collision_point = vec_sum(collision_point, game->player.pos);
		i++;
		if (game->map[(int)v_map_check.y][(int)v_map_check.x] == '1')
			tile_found = 1;
		else
			game->map[(int)v_map_check.y][(int)v_map_check.x] = 'B';
	}
	return (fill_collision(collision_point, distance,
			get_collision_orientation(last_step, v_step),
			get_texture_x(last_step, collision_point, v_map_check)));
}
