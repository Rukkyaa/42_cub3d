/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:20:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/24 14:35:59 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Draw a circle on the screen at position (x, y) with a given of radius and
** color.
**
** @param game: main game structure
** @param mid: position of the center of the circle
** @param radius: radius of the circle
** @param color: color of the circle
*/
void	draw_filled_circle(t_img *img, t_vector mid, int radius, int color)
{
	int	x;
	int	y;

	x = mid.x - radius;
	while (++x < mid.x + radius)
	{
		y = mid.y - radius;
		while (++y < mid.y + radius)
			if (pow(x - mid.x, 2) + pow(y - mid.y, 2) <= pow(radius, 2))
				img_pix_put(img, x, y, color);
	}
}
