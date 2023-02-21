/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/21 14:39:38 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;


	if(pixel_out_of_bound(x, y))
		return ;
	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

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
