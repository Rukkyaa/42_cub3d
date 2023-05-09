/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:15:48 by teliet            #+#    #+#             */
/*   Updated: 2023/05/09 12:00:18 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_raycast_two(t_game *game, t_raycast_data *d)
{
	if (d->v_ray_dir.y < 0)
	{
		d->v_step.y = -1;
		d->v_ray_length_1d.y = (game->player.pos.y
				- tile_to_pixel(d->v_map_check).y) / 64 * d->v_ray_unit_step.y;
	}
	else
	{
		d->v_step.y = 1;
		d->v_ray_length_1d.y = (tile_to_pixel(d->v_map_check).y + 64
				- game->player.pos.y) / 64 * d->v_ray_unit_step.y;
	}
}

void	init_raycast(t_game *game, t_vector3d direction, t_raycast_data *d)
{
	d->v_map_check = pixel_to_tile(game->player.pos);
	d->v_ray_dir = direction;
	d->v_ray_unit_step.x = sqrt(1 + (d->v_ray_dir.y / d->v_ray_dir.x)
			* (d->v_ray_dir.y / d->v_ray_dir.x));
	d->v_ray_unit_step.y = sqrt(1 + (d->v_ray_dir.x / d->v_ray_dir.y)
			* (d->v_ray_dir.x / d->v_ray_dir.y));
	if (d->v_ray_dir.x < 0)
	{
		d->v_step.x = -1;
		d->v_ray_length_1d.x = (game->player.pos.x
				- tile_to_pixel(d->v_map_check).x) / 64 * d->v_ray_unit_step.x;
	}
	else
	{
		d->v_step.x = 1;
		d->v_ray_length_1d.x = (tile_to_pixel(d->v_map_check).x + 64
				- game->player.pos.x) / 64 * d->v_ray_unit_step.x;
	}
	init_raycast_two(game, d);
}

void	fill_collision(t_raycast_data *d, char last_step)
{
	d->collision.distance = d->distance * 64;
	d->collision.orientation = get_collision_orientation(last_step, d->v_step);
	d->collision.x_pos_tex = get_texture_x(last_step, d->collision_point,
			d->v_map_check);
}

void	make_step(t_raycast_data *d)
{
	if (d->v_ray_length_1d.x < d->v_ray_length_1d.y)
	{
		d->last_step = 'x';
		d->v_map_check.x += d->v_step.x;
		d->distance = d->v_ray_length_1d.x;
		d->v_ray_length_1d.x += d->v_ray_unit_step.x;
	}
	else
	{
		d->last_step = 'y';
		d->v_map_check.y += d->v_step.y;
		d->distance = d->v_ray_length_1d.y;
		d->v_ray_length_1d.y += d->v_ray_unit_step.y;
	}
}

t_collision	cast_two_d_ray(t_game *game, t_vector3d direction)
{
	t_raycast_data	d;
	int				tile_found;

	tile_found = 0;
	d.distance = 0;
	init_raycast(game, direction, &d);
	while (!tile_found)
	{
		make_step(&d);
		d.collision_point = vec_scalar_mult(d.v_ray_dir, d.distance * 64);
		d.collision_point = vec_sum(d.collision_point, game->player.pos);
		if (is_wall(game->map[(int)d.v_map_check.y][(int)d.v_map_check.x]))
		{
			tile_found = 1;
			get_wall(game, &d.collision,
				game->map[(int)d.v_map_check.y][(int)d.v_map_check.x]);
		}
		else if (game->map[(int)d.v_map_check.y][(int)d.v_map_check.x] == 'D'
				&& handle_doors(game, &d, &tile_found))
			return (d.collision);
	}
	fill_collision(&d, d.last_step);
	return ((d.collision));
}
