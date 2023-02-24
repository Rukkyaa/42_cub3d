/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:58:16 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/22 14:19:02 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Draw a filled square on the screen at position (x, y) with a given of width
** and color.
**
** @param game: main game structure
** @param pos: position of the top left corner of the square
** @param width: width of the square
** @param color: color of the square
*/
void	draw_filled_square(t_game *game, t_vector vec, int width, int color)
{
	int			i;
	t_vector	pos;

	i = -1;
	while (++i < width)
	{
		pos.x = vec.x;
		pos.y = vec.y + i;
		draw_vertical_line(game, pos, width, color);
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
void	draw_square(t_game *game, t_vector pos, int width, int color)
{
	int			i;
	t_vector	vec;

	vec.x = pos.x;
	vec.y = pos.y;
	i = -1;
	while (++i < width)
	{
		img_pix_put(&game->img, vec.x, vec.y + i, color);
		img_pix_put(&game->img, vec.x + width - 1, vec.y + i, color);
	}
	draw_vertical_line(game, vec, width, color);
	vec.y = pos.y + width - 1;
	draw_vertical_line(game, vec, width, color);
}
