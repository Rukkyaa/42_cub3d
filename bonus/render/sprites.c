/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:31:27 by theo              #+#    #+#             */
/*   Updated: 2023/03/07 15:38:10 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// void    render_sprites(t_game *game)
// {
//     t_vector3d player_to_sprite;
//     player_to_sprite.x = game->sprites[0].pos.x - game->player.pos3d.x;
//     player_to_sprite.y = game->sprites[0].pos.y - game->player.pos3d.y;
//     player_to_sprite.z = game->sprites[0].pos.z;

//     t_vector standard_vec;
//     standard_vec.x = 1;
//     standard_vec.y = 1;
//   float CS=cos(vec_angle(game->player.direction, standard_vec)), SN=sin(vec_angle(game->player.direction, standard_vec)); //rotate around origin
//   float a = player_to_sprite.y * CS + player_to_sprite.x * SN; 
//   float b= player_to_sprite.x *CS-player_to_sprite.y*SN; 
//   player_to_sprite.x = a;
//   player_to_sprite.y= b;

//     t_vector screen_pos;
//   screen_pos.x =(player_to_sprite.x * 108.0 / player_to_sprite.y) + (RES_X/2); //convert to screen x,y
//   screen_pos.y =(player_to_sprite.z *108.0 / player_to_sprite.y)+ (RES_Y/2);

// //   mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, 0,0);
//   mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, screen_pos.x, screen_pos.y);
// }
t_vector vec_3d_to_2D(t_vector3d input) 
{
    t_vector output;

    output.x = input.x;
    output.y = input.y;
    return (output);
}

void    render_sprites(t_game *game)
{
    t_vector player_to_sprite;
    player_to_sprite.x = game->sprites[0].pos.x - game->player.pos3d.x;
    player_to_sprite.y = game->sprites[0].pos.y - game->player.pos3d.y;
   // player_to_sprite.z = game->sprites[0].pos.z;
    draw_line_dda(&game->img, game->player.pos, vec_sum(game->player.pos, player_to_sprite), RED_PIXEL);
    float inv_det = 1.0 / ((game->camera.proj_plane_width * game->player.direction.y) - (game->camera.proj_plane_height * game->player.direction.x));
    
    float transformX = inv_det * (game->player.direction.y * player_to_sprite.x - player_to_sprite.y * player_to_sprite.y);
    float transformY = inv_det * (-game->camera.proj_plane_height * player_to_sprite.x - player_to_sprite.y * game->camera.proj_plane_width);

    t_vector screen_pos;
    screen_pos.x =(RES_X / 2) * (1 + transformX / transformY); //convert to screen x,y
    screen_pos.y = abs((int) (RES_Y / transformY));
    vec_print(&screen_pos, "screen_pos");
    draw_filled_circle(&game->img, vec_3d_to_2D(game->sprites[0].pos), 5, BLUE_PIXEL);
//   mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, 0,0);
    mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, screen_pos.x, screen_pos.y);
}