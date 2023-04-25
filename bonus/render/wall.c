/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:23:05 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 10:28:17 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_wall(char c)
{
	return (c == '1' || c == '2' || c == '3' || c == '4');
}

void	get_wall(t_game *game, t_collision *collision, char c)
{
	if (c == '1')
		collision->wall = game->texture.wall1;
	else if (c == '2')
		collision->wall = game->texture.wall2;
	else if (c == '3')
		collision->wall = game->texture.wall3;
	else if (c == '4')
		collision->wall = game->texture.wall4;
	else if (c == 'D')
		collision->wall = game->texture.door;
}

void	shading_wall(t_game *game, int *pixel_color, t_wall_task d)
{
	if (HD && d.collision.distance > 320)
		*pixel_color = add_shade(*pixel_color, fmin(fmax(1
						- (d.collision.distance - 320) / 512, 0), 1) * 255);
}

void	wall_thread(t_game *game, t_wall_task d)
{
	int	i;
	int	x_text;
	int	pixel_color;
	int	max_i;
	int	offset;

	max_i = (int)fmin(RES_Y - 1, d.line_pos.y);
	offset = -(d.line_pos.y - d.line_height);
	game->z_buffer[(int)d.line_pos.x] = d.collision.distance;
	x_text = (int)((d.collision.x_pos_tex / 64.0f) * d.collision.wall.width);
	i = (int)fmax(0, d.line_pos.y - d.line_height);
	while (i < max_i)
	{
		if (d.collision.distance > 1000)
			img_pix_put(&game->fps_img, d.line_pos.x, i, BLACK_PIXEL);
		else
		{
			pixel_color = img_pix_read(&d.collision.wall, x_text, (((float)(i
								+ offset) / (float)d.line_height)
						* d.collision.wall.heigth));
			shading_wall(game, &pixel_color, d);
			img_pix_put(&game->fps_img, d.line_pos.x, i, pixel_color);
		}
		i++;
	}
}

// void	glitched_wall_thread(t_game *game, t_wall_task d)
// {
// 	int i;
// 	int x_text;
// 	int y_text;
// 	int pixel_color;
// 	int min_i;
// 	int max_i;
// 	int offset;

// 	i = (int)fmax(0, d.line_pos.y - d.line_height);
// 	max_i = (int)fmin(RES_Y - 1, d.line_pos.y);
// 	offset = (d.line_pos.y - d.line_height);
// 	game->z_buffer[(int)d.line_pos.x] = d.collision.distance;
// 	x_text = (int)((d.collision.x_pos_tex / 64.0f) * d.collision.wall.width);
// 	while (i < max_i)
// 	{
// 		if (d.collision.distance > 1000)
// 		{
// 			img_pix_put(&game->fps_img, d.line_pos.x, i, BLACK_PIXEL);
// 			i++;
// 			continue ;
// 		}
// 		y_text = (int)(((float)(i + offset) / (float)d.line_height)
// 				* d.collision.wall.heigth);
// 		pixel_color = img_pix_read(&d.collision.wall, x_text, y_text);
// 		if (HD && d.collision.distance > 320)
// 			pixel_color = add_shade(pixel_color, fmin(fmax(1
// 							- (d.collision.distance - 320) / 512, 0), 1) * 255);
// 		img_pix_put(&game->fps_img, d.line_pos.x, i, pixel_color);
// 		i++;
// 	}
// }
