/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:58:16 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/08 12:11:37 by axlamber         ###   ########.fr       */
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
void	draw_filled_square(t_vector vec, int width, int color)
{
	int			i;
	t_vector	pos;

	i = -1;
	while (++i < width)
	{
		pos.x = vec.x;
		pos.y = vec.y + i;
		draw_vertical_line(pos, width, color);
	}
}
