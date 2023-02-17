/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:38:51 by teliet            #+#    #+#             */
/*   Updated: 2023/02/17 10:44:26 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_game *game, int x, int y, int width, int color)
{
	int	i;

	i = -1;
	while (++i < width)
		draw_vertical_line(game, x, y + i, width, color);
}

// void draw_circle(t_game *game, t_vector center, int radius, int color)
// {
//     int x = center.x - radius;
//     while (x <= center.x  + radius) {
//         int y = center.y - radius;
//         while (y <=  center.y  + radius) {
//             float distance = sqrt((x - center.x ) * (x - center.x ) + (y -  center.y) * (y -  center.y));
//             if (distance <= radius) {
//                 //my_mlx_pixel_put(&model->img, x, y, 8888);
// 				mlx_pixel_put(game->mlx, game->win, x, y, color);
//             }
//             y++;
//         }
//         x++;
//     }
// }


void	draw_vertical_line(t_game *game, int x, int y, int len, int color)
{
	int	i;

	i = -1;
	while (++i < len)
		mlx_pixel_put(game->mlx, game->win, x + i, y, color);
}

void draw_line(t_game *game, t_vector posA, t_vector posB, int thickness, int color) 
{
    // Calculate the difference between the two points
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
    float delta_error = 2 * (dx - dy);
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
                mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
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
           mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
        }
    }
}

void    draw_filled_circle(t_game *game, t_vector center, int radius, int color) {
    int x, y;
    int x_start = center.x - radius;
    int x_end = center.x + radius;
    int y_start = center.y - radius;
    int y_end = center.y + radius;
    float r_squared = pow(radius, 2);

    for (x = x_start; x <= x_end; x++) {
        for (y = y_start; y <= y_end; y++) {
            float distance_squared = pow(x - center.x, 2) + pow(y - center.y, 2);

            if (distance_squared <= r_squared) {
                mlx_pixel_put(game->mlx, game->win, x, y, color);
            }
        }
    }
}