/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:38:51 by teliet            #+#    #+#             */
/*   Updated: 2023/02/17 11:58:01 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_filled_square(t_game *game, int x, int y, int width, int color)
{
	int	i;

	i = -1;
	while (++i < width)
		draw_vertical_line(game, x, y + i, width, color);
}

void	draw_square(t_game *game, int x, int y, int width, int color)
{
	int	i;

	i = -1;
	while (++i < width)
	{
		mlx_pixel_put(game->mlx, game->win, x, y + i, color);
		mlx_pixel_put(game->mlx, game->win, x + width - 1, y + i, color);	
	}
	draw_vertical_line(game, x, y + width - 1, width, color);	
	draw_vertical_line(game, x, y, width, color);	
}

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

void    draw_filled_circle(t_game *game, t_vector mid, int radius, int color)
{
	int	x;
	int	y;

	x =  mid.x - radius;
	while (++x < mid.x + radius)
	{
		y = mid.y - radius;
		while (++y < mid.y + radius)
            if (pow(x - mid.x, 2) + pow(y - mid.y, 2) <= pow(radius, 2))
                mlx_pixel_put(game->mlx, game->win, x, y, color);
    }
}

void	load_grid(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			if (game->map[i][j] == '1')
				draw_square(game, j * 64, i * 64, 64, 0xFFFFFF);
			else
				draw_square(game, j * 64, i * 64, 64, 0xFFFFFF);
		}
	}
}
