/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:17:19 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/26 14:48:19 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	pixel_out_of_bound(float x, float y, t_img *image)
{
	t_vector3d	pixel_coord;

	pixel_coord.x = x;
	pixel_coord.y = y;
	return (!(0 <= pixel_coord.x && pixel_coord.x < image->width * 64
			&& 0 <= pixel_coord.y && pixel_coord.y < image->heigth * 64));
}

t_vector3d	tile_to_pixel(t_vector3d tile_coord)
{
	t_vector3d	pixel_coord;

	pixel_coord.x = (int)(tile_coord.x * 64.0f);
	pixel_coord.y = (int)(tile_coord.y * 64.0f);
	return (pixel_coord);
}

int	divide_by_64(int value)
{
	return (value >> 6);
}

t_vector3d	pixel_to_tile(t_vector3d vector)
{
	t_vector3d	tile_coord;

	tile_coord.x = divide_by_64(vector.x);
	tile_coord.y = divide_by_64(vector.y);
	return (tile_coord);
}
