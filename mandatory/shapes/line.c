/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/21 15:28:07 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line_2(t_img *img, t_vector pos, int len, int color)
{
	int	i;

	i = -1;
	while (++i < len)
		img_pix_put(img, pos.x , pos.y + i, color);
}


void	draw_vertical_line(t_game *game, t_vector pos, int len, int color)
{
	int	i;

	i = -1;
	while (++i < len)
		img_pix_put(&game->img, pos.x + i, pos.y, color);
}

void draw_line_dda(t_img *img, t_vector vec1, t_vector vec2, int color) {
    int x1 = vec1.x;
    int y1 = vec1.y;
    int x2 = vec2.x;
    int y2 = vec2.y;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    float x_inc, y_inc, x = x1, y = y1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    x_inc = dx / (float) steps;
    y_inc = dy / (float) steps;

    int i = 0;
    while (i <= steps) {
        int ix = round(x);
        int iy = round(y);
        img_pix_put(img, ix, iy, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

void draw_line(t_game *game, t_vector posA, t_vector posB, int thickness, int color) 
{
    float dx = posB.x - posA.x;
    float dy = posB.y - posA.y;

    // Determine the direction of the line along the x and y axes
    int x_dir = dx > 0 ? 1 : -1;
    int y_dir = dy > 0 ? 1 : -1;

    // Determine the absolute values of the differences in x and y
    dx = fabsf(dx);
    dy = fabsf(dy);

    // Calculate the error term and the delta values
    float error = dx - dy;
    float delta_x = x_dir;
    float delta_y = y_dir;

    // Set up the initial coordinates of the line
    int x = (int) posA.x;
    int y = (int) posA.y;

    // Draw the line using put_pixel
    while (x != (int) posB.x || y != (int) posB.y) {
        // Draw a rectangle at the current position
        for (int i = 0; i < thickness; i++) {
            for (int j = 0; j < thickness; j++) {
				img_pix_put(&game->img, x + i, y + j, color);
                // mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
            }
        }

        // Update the error term and the position of the line
        float error2 = 2 * error;
        if (error2 > -dy) {
            error -= dy;
            x += delta_x;
        }
        if (error2 < dx) {
            error += dx;
            y += delta_y;
        }
    }

    // Draw a rectangle at the end position to complete the line
    for (int i = 0; i < thickness; i++) {
        for (int j = 0; j < thickness; j++) {
			img_pix_put(&game->img, x + i, y + j, color);
        //    mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
        }
    }
}
