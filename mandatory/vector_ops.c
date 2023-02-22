/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:20:57 by teliet            #+#    #+#             */
/*   Updated: 2023/02/22 11:47:44 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	pixel_out_of_bound(float x, float y, t_img *image)
{
	t_vector	pixel_coord;

	pixel_coord.x = x;
	pixel_coord.y = y;
	return (!(0 <= pixel_coord.x && pixel_coord.x < image->width * 64
			&& 0 <= pixel_coord.y && pixel_coord.y < image->heigth * 64));
}

int	tile_out_of_bound(t_vector tile_coord, t_game *game)
{
	return (!(0 <= tile_coord.x && tile_coord.x < game->img.width
			&& 0 <= tile_coord.y && tile_coord.y < game->img.heigth));
}

t_vector	tile_to_pixel(t_vector tile_coord)
{
	t_vector	pixel_coord;

	pixel_coord.x = (int)(tile_coord.x * 64.0f);
	pixel_coord.y = (int)(tile_coord.y * 64.0f);
	return (pixel_coord);
}

t_vector	pixel_to_tile(t_vector vector)
{
	t_vector	tile_coord;

	tile_coord.x = (int)(vector.x / 64.0f);
	tile_coord.y = (int)(vector.y / 64.0f);
	return (tile_coord);
}

//vec_rotate
t_vector	rotate2(t_vector vector, float angle)
{
	t_vector	output;
	float		cosine;
	float		sine;
	float		x;
	float		y;

	angle = angle * M_PI / 180.0f;
	cosine = cosf(angle);
	sine = sinf(angle);
	x = vector.x * cosine - vector.y * sine;
	y = vector.x * sine + vector.y * cosine;
	output.x = x;
	output.y = y;
	return (output);
}

//vec_rotate_edit
void	rotate(t_vector *vector, float angle)
{
	float	cosine;
	float	sine;
	float	x;
	float	y;

	angle = angle * M_PI / 180.0f;
	cosine = cosf(angle);
	sine = sinf(angle);
	x = vector->x * cosine - vector->y * sine;
	y = vector->x * sine + vector->y * cosine;
	vector->x = x;
	vector->y = y;
}
