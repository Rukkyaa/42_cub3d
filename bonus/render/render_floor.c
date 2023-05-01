/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:23:54 by teliet            #+#    #+#             */
/*   Updated: 2023/05/01 15:39:16 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	get_floor_intersection(t_vector3d position, t_vector3d direction)
{
	t_vector3d	intersection;
	double		t;

	t = -position.z / direction.z;
	intersection.x = position.x + t * direction.x;
	intersection.y = position.y + t * direction.y;
	intersection.z = 0;
	return (intersection);
}

int	get_floor_color(t_vector3d intersection, t_img *img)
{
	t_vector3d	v_texture_pos;

	v_texture_pos.x = fmod(intersection.x, 64);
	v_texture_pos.y = fmod(intersection.y, 64);
	return (img_pix_read(img, v_texture_pos.x, v_texture_pos.y));
}

void	shading_floor(t_game *game, int *pixel_color, int *shade,
		t_vector3d v3d_intersect_point)
{
	float	distance;

	if (HD && *shade)
	{
		distance = vec_distance(game->player.pos, v3d_intersect_point);
		if (distance > 320)
			*pixel_color = add_shade(*pixel_color, fmin(fmax(1 - (distance
								- 320) / 512, 0), 1) * 255);
		else
			*shade = 0;
	}
}

void	render_floor_unicolor(t_game *game, t_vector3d line_pos)
{
	int			i;
	t_roof_data	d;

	i = line_pos.y;
	d.img_addr = (unsigned int *)img_get_addr(&game->fps_img, line_pos.x, i);
	while (i < RES_Y)
	{
		*d.img_addr = game->floor_color;
		d.img_addr += RES_X;
		i++;
	}
}

void	render_floor(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos)
{
	int			i;
	t_roof_data	d;

	i = line_pos.y;
	d.shade = 1;
	d.img_addr = (unsigned int *)img_get_addr(&game->fps_img, line_pos.x, i);
	while (i < RES_Y)
	{
		d.v3d_intersect_point = vec_sum(game->player.pos,
				vec_scalar_mult(v_ray_dir,
					game->row_dist[(int)line_pos.x][i]));
		d.pixel_color = get_floor_color(d.v3d_intersect_point,
				&game->texture.ground);
		shading_floor(game, &d.pixel_color, &d.shade, d.v3d_intersect_point);
		*d.img_addr = d.pixel_color;
		d.img_addr += RES_X;
		i++;
	}
}
