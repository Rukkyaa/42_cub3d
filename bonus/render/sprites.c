/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:31:27 by theo              #+#    #+#             */
/*   Updated: 2023/03/08 12:31:43 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float   deg_to_rad(float angle)
{
    return angle * M_PI / 180.0f;
}

void    render_sprites(t_game *game)
{
    t_vector player_to_sprite;
    float angle;
    player_to_sprite.x = game->sprites[0].pos.x - game->player.pos.x;
    player_to_sprite.y = game->sprites[0].pos.y - game->player.pos.y;
    
    angle = vec_angle(game->player.direction, player_to_sprite);
    // printf("player_sprite_angle : %f\n", angle);
    vec_rotate_edit(&player_to_sprite, -game->player.angle);
    // printf("player_sprite_angle_rotated : %f\n", angle);
    float z_angle = vec_angle(game->player.direction, player_to_sprite);
    t_vector screen_pos;
    // player_to_sprite = vec_normalize(player_to_sprite);



    // Y AXIS ON SCREEN
    float xy_distance = sqrt(player_to_sprite.x * player_to_sprite.x + player_to_sprite.y * player_to_sprite.y);
    // printf("xy_distance : %f\n", xy_distance);
    t_vector z_vector;
    z_vector.x = xy_distance;
    z_vector.y = game->sprites[0].pos.z - 32;
    // vec_print(&z_vector, "z_vector");
    float y_dist = (z_vector.y / z_vector.x);
    // printf("y_dist: %f\n", y_dist);
    y_dist = y_dist * ( (float) RES_Y / 2.0f) ; 
    // printf("y_dist scaled: %f\n", y_dist);

    
    // X AXIS ON SCREEN
    // vec_print(&player_to_sprite, "player to sprite");
    // printf("proj dist : %f\n", game->camera.proj_plane_distance);
    float x_dist = (player_to_sprite.y / player_to_sprite.x) ;
    // printf("x dist : %f\n", x_dist);
    x_dist = x_dist * ( (float) RES_X / 2) ; // scaline x_dist
    // printf("x dist scaled : %f\n", x_dist);
    screen_pos.x =  x_dist + RES_X / 2;
    screen_pos.y =  - y_dist + (RES_Y / 2);
    // printf("screen_pos_x : %f\n", screen_pos.x );
//   screen_pos.x =(player_to_sprite.x * 1 / player_to_sprite.y) + (RES_X / 2); //convert to screen x,y
//   screen_pos.y =(player_to_sprite.z * 1 / player_to_sprite.y) + (RES_Y / 2);

    // TODO : add condition if angle too wide
    if(fabs(angle) > (float) FOV_RADIANS / 2)
        return ;
    
//   mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, 0,0);
  mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, screen_pos.x - game->sprites[0].texture.width/2, 
        screen_pos.y - game->sprites[0].texture.heigth/2);
}
t_vector vec_3d_to_2D(t_vector3d input) 
{
    t_vector output;

    output.x = input.x;
    output.y = input.y;
    return (output);
}

// void    render_sprites(t_game *game)
// {
//     t_vector player_to_sprite;
//     player_to_sprite.x = game->sprites[0].pos.x - game->player.pos3d.x;
//     player_to_sprite.y = game->sprites[0].pos.y - game->player.pos3d.y;
//    // player_to_sprite.z = game->sprites[0].pos.z;
//     draw_line_dda(&game->img, game->player.pos, vec_sum(game->player.pos, player_to_sprite), RED_PIXEL);
//     float inv_det = 1.0 / ((game->camera.plane.x * game->player.direction.y) - (game->camera.plane.y * game->player.direction.x));
    
//     float transformX = inv_det * (game->player.direction.y * player_to_sprite.x - game->player.direction.x * player_to_sprite.y);
//     float transformY = inv_det * (-game->camera.plane.y * player_to_sprite.x - player_to_sprite.y * game->camera.plane.x);

//     t_vector screen_pos;
//     screen_pos.x =(RES_X / 2) * (1 + transformX / transformY); //convert to screen x,y
//     screen_pos.y = fabs((RES_Y / transformY));
//     vec_print(&screen_pos, "screen_pos");
//     draw_filled_circle(&game->img, vec_3d_to_2D(game->sprites[0].pos), 5, BLUE_PIXEL);
// //   mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, 0,0);
//     mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, screen_pos.x, screen_pos.y);
// }