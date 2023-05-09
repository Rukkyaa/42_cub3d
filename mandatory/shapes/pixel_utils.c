/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:17:19 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/09 13:11:51 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pixel_out_of_bound(float x, float y, t_img *image)
{
	t_vector	pixel_coord;

	(void)image;
	pixel_coord.x = x;
	pixel_coord.y = y;
	return (!(0 <= pixel_coord.x && pixel_coord.x < RES_X
			&& 0 <= pixel_coord.y && pixel_coord.y < RES_Y));
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
