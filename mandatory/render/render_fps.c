/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/04/11 14:35:53 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    basic_render(t_game *game, t_collision collision, t_vector line_pos, double line_height)
{
    if(collision.orientation == 'S' || collision.orientation == 'N')
        draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE);
    else
        draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE_SHADED);  
}

void texture_render(t_game *game, t_collision collision, t_vector line_pos, double line_height)
{
    int i = -1;
    int j = 0;
    int x_text = 0;
    int y_text = 0;
    int pixel_color;

	while (++i < line_pos.y)
		img_pix_put(&game->fps_img, line_pos.x, i, 0x696969);
	i = 0;
    
    while(i < line_height)
    {
        x_text = (int) collision.x_pos_tex;
        y_text = (int) ((i / line_height) * 64);
        pixel_color =  img_pix_read(&game->texture.wall, x_text, y_text) ;
        img_pix_put(&game->fps_img, line_pos.x, line_pos.y + i, pixel_color);
        i++;
    }
	while (i < RES_Y)
		img_pix_put(&game->fps_img, line_pos.x, line_pos.y + i++, 0x8b668b);
}

void    render_fps(t_game *game)
{
    int i = 0;
    float distance;
    float line_height;
    t_collision collision;
    t_vector v_right;
    t_vector line_pos;
    t_vector v_ray_dir;
    t_vector v_player_to_camera_plane;
    float halfWidth;
    float offset;
    halfWidth = tanf((float)FOV_RADIANS / 2.0f) * game->player.direction_adjust ;
    v_right  = vec_normalize(vec_rotate(game->player.direction, 90)) ;
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->player.direction_adjust);
    line_pos.x = 0;
    while(i < RES_X)
    {
        offset = ((2.0f * (float) line_pos.x / (RES_X - 1.0f)) - 1.0f) * halfWidth;
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, offset));
        v_ray_dir = vec_normalize(v_ray_dir);
        collision = cast_2D_ray(game, v_ray_dir);
        float ca = vec_angle(v_ray_dir, game->player.direction);
        collision.distance  = collision.distance * cosf(ca);
        line_height = ( 64 / collision.distance ) * game->player.direction_adjust  ;
        line_pos.y = RES_Y / 2 - line_height / 2;
        texture_render(game, collision, line_pos, line_height);
        i++;
        line_pos.x+= RES_X / RES_X;
    }
}
