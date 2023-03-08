/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:31:27 by theo              #+#    #+#             */
/*   Updated: 2023/03/08 18:19:55 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float   deg_to_rad(float angle)
{
    return angle * M_PI / 180.0f;
}

int     sample_img(t_img *img, float x, float y)
{
    return (img_pix_read(img, x * img->width, y * img->heigth));
}

void   draw_sprite(t_game *game, t_vector screen_pos, float xy_distance, t_sprite *sprite)
{
    t_vector start_pos;
    float line_height =   (RES_Y / game->camera.proj_plane_height) * (sprite->height / xy_distance ) * game->camera.proj_plane_distance;
    float line_width = (RES_X / game->camera.proj_plane_width ) * (sprite->width / xy_distance ) * game->camera.proj_plane_distance;
    int pixel_color;

    // Start
    start_pos.x = fmax(screen_pos.x - line_width / 2, 0);
    start_pos.y = fmax(screen_pos.y - line_height, 0);

    // End
    int max_i = fmin(screen_pos.x + line_width / 2, RES_X - 1);
    int max_j = fmin(screen_pos.y, RES_Y - 1);
    
    vec_print(&screen_pos, "screen_pos");
    vec_print(&start_pos, "start_pos");
    printf("max_i : %d\n", max_i);
    printf("max_j : %d\n", max_j);
    printf("line_height : %f\n", line_height);
    printf("line_width : %f\n", line_width);
    float i = start_pos.x;
    float j = start_pos.y;
    while(i < max_i)
    {
        j = start_pos.y;
        while(j < max_j)
        {
            // printf("x_pos : %f\n",(i - (screen_pos.x - (line_width / 2))) / line_width);
            // printf("y_pos : %f\n", start_pos.y - j);
            pixel_color = sample_img(&sprite->texture, (i - (screen_pos.x - (line_width / 2))) / line_width, (j - (screen_pos.y - line_height)) / line_width);
            // printf("%d %d : %d\n", i, j, pixel_color);
            if(get_t(pixel_color) == 0)
                img_pix_put(&game->fps_img,  i,  j, pixel_color);
            //sample_texture( (float) i / line_width,  (float) i / line_height, &sprite->texture);
            j++;
        }
        i++;
    }
    // close_window(game);
}

void    render_sprites(t_game *game)
{
    t_vector player_to_sprite;
    t_vector screen_pos;
    float angle;
    
    player_to_sprite.x = game->sprites[0].pos.x - game->player.pos.x;
    player_to_sprite.y = game->sprites[0].pos.y - game->player.pos.y;
    
    // X AXIS ON SCREEN
    angle = vec_angle(game->player.direction, player_to_sprite);
    vec_rotate_edit(&player_to_sprite, -game->player.angle);
    float x_dist = (player_to_sprite.y / player_to_sprite.x);
    x_dist = x_dist * ( (float) RES_X / 2);

    // Y AXIS ON SCREEN
    float xy_distance = sqrt(player_to_sprite.x * player_to_sprite.x + player_to_sprite.y * player_to_sprite.y);
    t_vector z_vector;
    z_vector.x = xy_distance;
    z_vector.y = game->sprites[0].pos.z - 32;
    float y_dist = (z_vector.y / z_vector.x);
    y_dist = y_dist * ( (float) RES_Y / 2.0f) ; 

    screen_pos.x =  x_dist + RES_X / 2;
    screen_pos.y =  - y_dist + (RES_Y / 2);

    if(fabs(angle) > M_PI / 2)
        return ;

    draw_sprite(game, screen_pos, xy_distance, &game->sprites[0]);
    // mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, screen_pos.x - game->sprites[0].texture.width/2, 
    //         screen_pos.y - game->sprites[0].texture.heigth/2);
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