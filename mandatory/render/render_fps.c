/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/02/21 13:15:25 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void    render_fps(t_game *game)
// {
//     int i = 0;
//     float distance;
//     t_vector line_pos;
//     int line_size;
//     float ray_increment_radians = FOV_RADIANS / RES_X;
//     float current_angle;
//     // printf("ray increment : %f \n", ray_increment_radians);
//     // initialise direction of raycast to left_most
//     t_vector v_ray_dir;
//     v_ray_dir.x = game->player.direction.x;
//     v_ray_dir.y = game->player.direction.y;
//     // print_vector2D(&v_ray_dir, "raycast dir");
//     rotate(&v_ray_dir, M_PI * 2 - ray_increment_radians * 20 * RES_X / 2);
//     // current_angle = 
//     line_pos.x = 0;
//     while(i < RES_X)
//     {
//         line_pos.x++;
//         // print_vector2D(&v_ray_dir, "raycast dir");
// 	    distance = cast_2D_ray(game, v_ray_dir);
//         // printf("distance : %d \n", distance);
//         rotate(&v_ray_dir, ray_increment_radians * 20);
//         line_size = (8 - distance) * 50;
//         line_pos.y = RES_Y / 2 - line_size / 2;
//         draw_vertical_line_2(&game->fps_img, line_pos, line_size, 100 - distance * 50);
//         i++;
//     }
//     // close_window(game);
// }

t_vector get_vector(float x, float y)
{
    t_vector vec;
    
    vec.x = x;
    vec.y = y;

    return vec;
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
    float halfWidth;
    float offset;
    halfWidth = tan(FOV / 2) / 2;
    v_right  = rotate2(game->player.direction, 90);
    v_ray_dir.x = game->player.direction.x;
    v_ray_dir.y = game->player.direction.y;
    line_pos.x = 0;
    while(i < RES_X)
    {
        line_pos.x++;
        offset = ((2.0 * i / (RES_X - 1.0)) - 1.0) * halfWidth;
        v_ray_dir = vec_sum(game->player.direction, vec_scalar_mult(v_right, offset));
        // printf("%d : ", line_pos.x);
        // print_vector2D(&v_ray_dir, "raycast dir");
        collision = cast_2D_ray(game, v_ray_dir);
        // printf("distance : %d \n", distance);
        line_height = (RES_Y - (collision.distance / MAX_DISTANCE) * RES_Y );
        line_pos.y = RES_Y / 2 - line_height / 2;
        // printf("orientation : %c\n", collision.orientation);
            //draw_filled_circle(&game->fps_img, get_vector(1000, 400), line_height, PALE_BLUE);
        // if ((int) collision.point.x % 64 < 2  || (int) collision.point.y % 64 < 2) // 64 - (int) collision.point.x % 64 < 2 || 64 - (int) collision.point.y % 64 < 2
        //     draw_vertical_line_2(&game->fps_img, line_pos, line_size, RED_PIXEL);
        if(collision.orientation == 'S' || collision.orientation == 'O')
            draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE);
        else
            draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE_SHADED);
        i++;
        // img_pix_put(&game->fps_img, line_pos.x, 400, RED_PIXEL);
    }
    // close_window(game);
}
