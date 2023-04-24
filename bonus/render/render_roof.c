/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_roof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:58:52 by teliet            #+#    #+#             */
/*   Updated: 2023/04/24 15:29:14 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// to do : get texture of the specific tile hit
// divide v_texture_pos by 64 to enable higher resolution
// + use return(sample_img(img, v_texture_pos.x, v_texture_pos.y));
int	get_roof_color(t_game *game, t_vector3d intersection, t_img *img)
{
	t_vector3d	v_texture_pos;
	t_vector3d	v_tile;

	v_tile.x = (int)intersection.x / 64;
	v_tile.y = (int)intersection.y / 64;
	if (game->map[(int)v_tile.y][(int)v_tile.x] == 'E')
		return (0xff001010);
	v_texture_pos.x = fmod(intersection.x, 64);
	v_texture_pos.y = fmod(intersection.y, 64);
	return (img_pix_read(img, v_texture_pos.x, v_texture_pos.y));
}

void	shading_roof(t_game *game, int *pixel_color, int *shade,
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

void	render_roof(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos,
		float line_height)
{
	t_roof_data	d;
	int			i;

	i = line_pos.y - line_height - 1;
	d.shade = 1;
	d.min = 0;
	if (line_pos.x < 224)
		d.min = 224;
	d.img_addr = (unsigned int *)img_get_addr(&game->fps_img, line_pos.x, i);
	while (i >= d.min)
	{
		d.v3d_intersect_point = vec_sum(game->player.pos,
				vec_scalar_mult(v_ray_dir,
					game->row_dist[(int)line_pos.x][i]));
		d.pixel_color = get_roof_color(game, d.v3d_intersect_point,
				&game->texture.roof);
		shading_roof(game, &d.pixel_color, &d.shade, d.v3d_intersect_point);
		*d.img_addr = d.pixel_color;
		d.img_addr -= RES_X;
		i--;
	}
}

void	pre_compute_rows_dist(t_game *game, t_vector3d line_pos,
		float line_height, float resize)
{
	int		i;
	float	dist;

	i = 0;
	while (i < line_pos.y - line_height)
	{
		dist = ((game->wall_height - game->player.pos3d.z)
				* game->camera.proj_plane_distance)
			/ (float)(game->camera.plane_center.y - i);
		dist /= resize;
		game->row_dist[(int)line_pos.x][i] = dist;
		i++;
	}
	i = line_pos.y;
	while (i < RES_Y)
	{
		dist = (game->player.pos3d.z * game->camera.proj_plane_distance)
			/ (float)(i - game->camera.plane_center.y);
		dist /= resize;
		game->row_dist[(int)line_pos.x][i] = dist;
		i++;
	}
}
