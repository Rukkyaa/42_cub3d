/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:31:27 by theo              #+#    #+#             */
/*   Updated: 2023/03/09 18:05:11 by teliet           ###   ########.fr       */
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

void   draw_sprite(t_game *game, t_sprite *sprite)
{
    t_vector start_pos;
    float line_height =   (RES_Y / game->camera.proj_plane_height) * (sprite->height / sprite->distance ) * game->camera.proj_plane_distance;
    float line_width = (RES_X / game->camera.proj_plane_width ) * (sprite->width / sprite->distance ) * game->camera.proj_plane_distance;
    int pixel_color;

    // Start
    start_pos.x = fmax(sprite->screen_pos.x - line_width / 2, 0);
    start_pos.y = fmax(sprite->screen_pos.y - line_height, 0);

    // End
    int max_i = fmin(sprite->screen_pos.x + line_width / 2, RES_X - 1);
    int max_j = fmin(sprite->screen_pos.y, RES_Y - 1);
    
    // vec_print(&screen_pos, "screen_pos");
    // vec_print(&start_pos, "start_pos");
    // printf("max_i : %d\n", max_i);
    // printf("max_j : %d\n", max_j);
    // printf("line_height : %f\n", line_height);
    // printf("line_width : %f\n", line_width);
    float i = start_pos.x;
    float j = start_pos.y;
    while(i < max_i)
    {
        j = start_pos.y;
        // printf("z_buff : %d\n", game->z_buffer[(int)i]);
        if(game->z_buffer[(int)i] < sprite->distance)
        {
            i++;
            continue;
        }
        while(j < max_j)
        {
            // printf("x_pos : %f\n",(i - (screen_pos.x - (line_width / 2))) / line_width);
            // printf("y_pos : %f\n", start_pos.y - j);
            pixel_color = sample_img(&sprite->texture, (i - (sprite->screen_pos.x - (line_width / 2))) / line_width, (j - (sprite->screen_pos.y - line_height)) / line_width);
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

void    render_sprite(t_game *game, t_sprite *sprite)
{
    t_vector player_to_sprite;
    t_vector screen_pos;
    float angle;
    
    player_to_sprite.x = sprite->pos.x - game->player.pos.x;
    player_to_sprite.y = sprite->pos.y - game->player.pos.y;
    
    // X AXIS ON SCREEN
    angle = vec_angle(game->player.direction, player_to_sprite);
    vec_rotate_edit(&player_to_sprite, -game->player.angle);
    float x_dist = (player_to_sprite.y / player_to_sprite.x);
    x_dist = x_dist * ( (float) RES_X / 2);

    // Y AXIS ON SCREEN
    float xy_distance = sqrt(player_to_sprite.x * player_to_sprite.x + player_to_sprite.y * player_to_sprite.y);
    t_vector z_vector;
    z_vector.x = xy_distance;
    z_vector.y = sprite->pos.z - 32;
    float y_dist = (z_vector.y / z_vector.x);
    y_dist = y_dist * ( (float) RES_Y / 2.0f) ; 

    screen_pos.x =  x_dist + RES_X / 2;
    screen_pos.y =  - y_dist + (RES_Y / 2);

    if(fabs(angle) > M_PI / 2)
    {
        sprite->visible = 0;
        return ;
    }

    sprite->visible = 1;
    sprite->distance = xy_distance;
    sprite->screen_pos = screen_pos;
    // mlx_put_image_to_window(game->mlx, game->fps_win, game->sprites[0].texture.mlx_img, screen_pos.x - game->sprites[0].texture.width/2, 
    //         screen_pos.y - game->sprites[0].texture.heigth/2);
}

void    render_sprites(t_game *game)
{
    int i = 10;

    while(i--)
        render_sprite(game, &game->sprites[i]);
    sort_sprites(game->sprites, 10);
    i = 10; 
    
    while(i--)
        if(game->sprites[i].visible)
            draw_sprite(game, &game->sprites[i]);
}

t_vector vec_3d_to_2D(t_vector3d input) 
{
    t_vector output;

    output.x = input.x;
    output.y = input.y;
    return (output);
}

