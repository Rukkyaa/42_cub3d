/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:58:16 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:40 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Draw a filled square on the screen at position (x, y) with a given of width
** and color.
**
** @param game: main game structure
** @param pos: position of the top left corner of the square
** @param width: width of the square
** @param color: color of the square
*/
void	draw_filled_square(t_img *img, t_vector3d vec, int width, int color)
{
	int			i;
	t_vector3d	pos;

	i = -1;
	while (++i < width)
	{
		pos.x = vec.x;
		pos.y = vec.y + i;
		draw_vertical_line(img, pos, width, color);
	}
}

/*
** Draw a filled square on the screen at position (x, y) with a given of width
** and color.
**
** @param game: main game structure
** @param pos: position of the top left corner of the square
** @param width: width of the square
** @param color: color of the square
*/
void	draw_square(t_img *img, t_vector3d pos, int width, int color)
{
	int			i;
	t_vector3d	vec;

	vec.x = pos.x;
	vec.y = pos.y;
	i = -1;
	while (++i < width)
	{
		img_pix_put(img, vec.x, vec.y + i, color);
		img_pix_put(img, vec.x + width - 1, vec.y + i, color);
	}
	draw_vertical_line(img, vec, width, color);
	vec.y = pos.y + width - 1;
	draw_vertical_line(img, vec, width, color);
}
