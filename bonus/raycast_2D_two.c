/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:38:11 by teliet            #+#    #+#             */
/*   Updated: 2023/04/27 10:51:29 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	handle_doors(t_game *game, t_raycast_data *d, char last_step,
		int *tile_found)
{
	t_vector3d	door_intersection;

	if (last_step == 'y')
	{
		door_intersection.x = fmod(d->collision_point.x, 64) + 32
			* (d->v_ray_dir.y / d->v_ray_dir.x);
		printf("ystep\n");
	}
	else
		door_intersection.y = d->collision_point.y + 32 * d->v_ray_dir.y
			/ fabs(d->v_ray_dir.x);
	if (((int)door_intersection.y) / 64 == d->v_map_check.y)
	{
		d->collision.x_pos_tex = ((int)door_intersection.y) % 64;
		d->collision.distance = d->distance * 64 + sqrtf(32 * 32
				+ pow(d->v_ray_dir.y / d->v_ray_dir.x * 32, 2));
		d->collision.orientation = get_collision_orientation(last_step,
				d->v_step);
		d->collision.point = d->collision_point;
		*tile_found = 1;
		get_wall(game, &d->collision,
			game->map[(int)d->v_map_check.y][(int)d->v_map_check.x]);
		return (1);
	}
	return (0);
}

char	get_collision_orientation(char last_step, t_vector3d v_step)
{
	if (last_step == 'x')
	{
		if (v_step.x == 1)
			return ('O');
		else
			return ('E');
	}
	else
	{
		if (v_step.y == 1)
			return ('N');
		else
			return ('S');
	}
}

double	get_texture_x(char last_step, t_vector3d v_collision_point,
		t_vector3d v_map_check)
{
	if (last_step == 'x')
		return (v_collision_point.y - v_map_check.y * 64);
	else
		return (v_collision_point.x - v_map_check.x * 64);
}
