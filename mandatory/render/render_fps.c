/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/02/19 14:52:57 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    render_fps(t_game *game)
{
    int i = 0;
    float distance;
    t_vector line_pos;
    int line_size;
    float ray_increment_radians = FOV_RADIANS / RES_X;
    // printf("ray increment : %f \n", ray_increment_radians);
    // initialise direction of raycast to left_most
    t_vector v_ray_dir;
    v_ray_dir.x = game->player.direction.x;
    v_ray_dir.y = game->player.direction.y;
    // print_vector2D(&v_ray_dir, "raycast dir");
    rotate(&v_ray_dir, M_PI * 2 - ray_increment_radians * 20 * RES_X / 2);
    
    line_pos.x = 0;
    while(i < RES_X)
    {
        line_pos.x++;
        // print_vector2D(&v_ray_dir, "raycast dir");
	    distance = cast_2D_ray(game, v_ray_dir);
        // printf("distance : %d \n", distance);
        rotate(&v_ray_dir, ray_increment_radians * 20);
        line_size = (8 - distance) * 50;
        line_pos.y = RES_Y / 2 - line_size / 2;
        draw_vertical_line_2(&game->fps_img, line_pos, line_size, distance * 50);
        i++;
    }
    // close_window(game);
}
