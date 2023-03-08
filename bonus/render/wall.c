/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:23:05 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/08 12:15:14 by axlamber         ###   ########.fr       */
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
}

void wall_render(t_collision collision, t_vector line_pos, double line_height)
{
    int i;
    int x_text = 0;
    int y_text = 0;
    int pixel_color;
    int min_i;
    int max_i;
    
    min_i = (int) fmax(0 , line_pos.y - line_height);
    max_i = (int) fmin(RES_Y - 1, line_pos.y );
    int offset = min_i - (line_pos.y - line_height);

    // Sky
    i = 0;
	while (i < min_i)
    {
		img_pix_put(&_mlx()->img, line_pos.x, i, 0x696969);
        i++;
    }
    while(i < max_i)
    {
        x_text = (int) ((collision.x_pos_tex / 64.0f) * collision.wall.width);
        y_text = (int) (((i + offset - min_i) / line_height) * collision.wall.heigth);
        pixel_color =  img_pix_read(&collision.wall, x_text, y_text) ;
        // printf("pixel %d %d : %ld\n", x_text, y_text, pixel_color);
        img_pix_put(&_mlx()->img, line_pos.x, i, pixel_color);
        i++;
    }
}
