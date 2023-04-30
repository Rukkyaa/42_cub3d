/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:38:11 by teliet            #+#    #+#             */
/*   Updated: 2023/04/30 16:15:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	handle_doors_x(t_game *game, t_raycast_data *d, char last_step,
		int *tile_found)
{
	t_vector3d	door_intersection;
	float door_offset;
	
	door_offset = 32 * d->v_ray_dir.y / fabs(d->v_ray_dir.x) - 32;
	door_intersection.y = d->collision_point.y + door_offset;
	if (((int)door_intersection.y) / 64 == d->v_map_check.y)
	{
		d->collision.x_pos_tex = ((int)door_intersection.y) % 64;
		if(d->collision.x_pos_tex > 32)
			return 0;
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

int	handle_doors_y(t_game *game, t_raycast_data *d, char last_step,
		int *tile_found)
{
	t_vector3d	door_intersection;
	float door_offset;
	
	door_offset = 32 * d->v_ray_dir.x / fabs(d->v_ray_dir.y) - 32;
	door_intersection.x = d->collision_point.x + door_offset;
	if (((int)door_intersection.x) / 64 == d->v_map_check.x)
	{
		d->collision.x_pos_tex = ((int)door_intersection.x) % 64;
		if(d->collision.x_pos_tex > 32)
			return 0;
		d->collision.distance = d->distance * 64 + sqrtf(32 * 32
				+ pow(d->v_ray_dir.x / d->v_ray_dir.y * 32, 2));
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


int	handle_doors(t_game *game, t_raycast_data *d, char last_step,
		int *tile_found)
{
	t_vector3d	door_intersection;
	float door_offset;

	if (last_step == 'y')
		return (handle_doors_y(game, d, last_step, tile_found));
	else
		return (handle_doors_x(game, d, last_step, tile_found));
	if (((int)door_intersection.y) / 64 == d->v_map_check.y)
	{
		d->collision.x_pos_tex = ((int)door_intersection.y) % 64;
		if(d->collision.x_pos_tex > 32)
			return 0;
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
