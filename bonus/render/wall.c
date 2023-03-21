/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:23:05 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/21 16:58:15 by teliet           ###   ########.fr       */
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

void wall_render(t_game *game, t_collision collision, t_vector3d line_pos, double line_height)
{
    int i;
    int x_text = 0;
    int y_text = 0;
    int pixel_color;
    int min_i;
    int max_i;
    unsigned int *img_addr;
    
    min_i = (int) fmax(0 , line_pos.y - line_height);
    max_i = (int) fmin(RES_Y - 1, line_pos.y );
    float offset = - (line_pos.y - line_height) / line_height;
    game->z_buffer[(int) line_pos.x] = collision.distance;
    
    img_addr = ( unsigned int *)img_get_addr(&game->fps_img, line_pos.x, 0);
    // Sky
    i = 0;
	while (i < min_i)
    {
		//img_pix_put(&game->fps_img, line_pos.x, i, 0x696969);
        i++;
        img_addr += RES_X;
    }
    i = min_i;
    while(i < max_i)
    {
        if(HD && collision.distance > 1000)
        {
            img_pix_put(&game->fps_img, line_pos.x, i, BLACK_PIXEL);
            i++;
            img_addr += RES_X;
            continue;
        }
        x_text = (int) (collision.x_pos_tex);
        y_text = (int) (((i / line_height )+ offset) * collision.wall.heigth);
        
        pixel_color =  img_pix_read(&collision.wall, x_text, y_text);
        if(HD && collision.distance > 320)
            pixel_color = add_shade(pixel_color, fmin(fmax(1 - (collision.distance  - 320 ) / 512, 0), 1) * 255) ; 
        *img_addr = pixel_color; 
        // printf("pixel %d %d : %ld\n", x_text, y_text, pixel_color);
        //img_pix_put(&game->fps_img, line_pos.x, i, pixel_color);
        img_addr += RES_X;
        i++;
    }
}
