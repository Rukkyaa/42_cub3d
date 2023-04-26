/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:12:31 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/04/26 14:47:41 by teliet           ###   ########.fr       */
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
void	draw_filled_rectangle(t_img *img, t_vector3d vec, t_vector3d size,
		int color)
{
	int			i;
	t_vector3d	pos;

	i = -1;
	while (++i < size.y)
	{
		pos.x = vec.x;
		pos.y = vec.y + i;
		draw_vertical_line(img, pos, size.x, color);
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
// void	draw_square(t_game *game, t_vector3d pos, int width, int color)
// {
// 	int			i;
// 	t_vector3d	vec;

// 	vec.x = pos.x;
// 	vec.y = pos.y;
// 	i = -1;
// 	while (++i < width)
// 	{
// 		img_pix_put(&game->debug_img, vec.x, vec.y + i, color);
// 		img_pix_put(&game->debug_img, vec.x + width - 1, vec.y + i, color);
// 	}
// 	draw_vertical_line(game, vec, width, color);
// 	vec.y = pos.y + width - 1;
// 	draw_vertical_line(game, vec, width, color);
// }
