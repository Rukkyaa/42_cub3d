/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/02/22 10:47:36 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void    render_fps(t_game *game)
// {
//     int i = 0;
//     float distance;
//     t_vector line_pos;
//     float line_height;
//     t_collision collision;
//     double ray_increment_radians = FOV_RADIANS / RES_X;
//     float ca;

//     t_vector v_ray_dir;
//     v_ray_dir.x = game->player.direction.x;
//     v_ray_dir.y = game->player.direction.y;
//     // print_vector2D(&v_ray_dir, "raycast dir");
//     rotate_rad(&v_ray_dir, M_PI * 2 - FOV_RADIANS / 2) ;
//     // current_angle = 
//     line_pos.x = 0;
//     while(i < RES_X)
//     {
//         line_pos.x+= RES_X / RES_X;
//         // print_vector2D(&v_ray_dir, "raycast dir");
// 	    collision = cast_2D_ray(game, v_ray_dir);
//         // printf("distance : %d \n", distance);
//         rotate_rad(&v_ray_dir, ray_increment_radians);
//         ca = angle_between_vectors(v_ray_dir, game->player.direction);
//         if(ca < 0 )
//             ca += 2 * M_PI;
//         if(ca > 2 * M_PI )
//             ca -= 2 * M_PI;
//         collision.distance *= cosf(ca);
//         line_height = ( (float) RES_Y - (collision.distance / (float) MAX_DISTANCE) * (float) RES_Y );
//         line_pos.y = RES_Y / 2 - line_height / 2;
//         if(collision.orientation == 'S' || collision.orientation == 'O')
//             draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE);
//         else
//             draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE_SHADED);
//         i++;
//     }
//     // close_window(game);
// }

// t_vector get_vector(float x, float y)
// {
//     t_vector vec;
    
//     vec.x = x;
//     vec.y = y;

//     return vec;
// }

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
    //printf("half_width : %f\n", halfWidth);
    v_right  = normalize(rotate2(game->player.direction, 90)) ;
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->player.direction_adjust);
    //draw_line_dda(&game->img, vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, halfWidth))),  vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, -halfWidth))), BLUE_PIXEL);
    // v_ray_dir.x = game->player.direction.x;s
    // v_ray_dir.y = game->player.direction.y;
    // v_ray_dir = vec_scalar_mult(game->player.direction, 5);
    line_pos.x = 0;
    while(i < RES_X)
    {
        offset = ((2.0f * (float) line_pos.x / (RES_X - 1.0f)) - 1.0f) * halfWidth;
        // printf("offset : %f\n", offset);
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, offset));
        v_ray_dir = normalize(v_ray_dir);
        // printf("angle : %f\n", angle_between_vectors(v_ray_dir, game->player.direction));
        // printf("%d : ", line_pos.x);
        // print_vector2D(&v_ray_dir, "raycast dir");
        collision = cast_2D_ray(game, v_ray_dir);
        // printf("distance : %d \n", distance);
        // line_height = (RES_Y * ( 1 - (collision.distance * 1 / MAX_DISTANCE));
        float ca = angle_between_vectors(v_ray_dir, game->player.direction);
        collision.distance  = collision.distance * cosf(ca);
        line_height = ( 64 / collision.distance ) * game->player.direction_adjust  ;
        line_pos.y = RES_Y / 2 - line_height / 2;
        // printf("orientation : %c\n", collision.orientation);
            //draw_filled_circle(&game->fps_img, get_vector(1000, 400), line_height, PALE_BLUE);
        // if ((int) collision.point.x % 64 < 2  || (int) collision.point.y % 64 < 2) // 64 - (int) collision.point.x % 64 < 2 || 64 - (int) collision.point.y % 64 < 2
        //     draw_vertical_line_2(&game->fps_img, line_pos, line_size, RED_PIXEL);
        if(collision.orientation == 'S' || collision.orientation == 'N')
            draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE);
        else
            draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE_SHADED);
        i++;
        // img_pix_put(&game->fps_img, line_pos.x, 400, RED_PIXEL);
        line_pos.x+= RES_X / RES_X;
    }
    // close_window(game);
    //draw_line_dda(&game->img, vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, halfWidth))),  vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, -halfWidth))), BLUE_PIXEL);
    // close_window(game);
}
