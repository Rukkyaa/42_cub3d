/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/04/24 15:24:28 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int my_abs(int n)
{
    if(n<0)
        n = -n;
    return n;
}

int     check_tile_shading(t_game *game, t_vector3d   pos)
{
    t_vector3d tile_pos = pixel_to_tile(pos);
    // vec_print(&tile_pos, "tile_pos");
    // vec_print(&game->player->tile_pos, "game->player");
    int distance = my_abs(tile_pos.x - game->player.tile_pos.x) + my_abs(tile_pos.y - game->player.tile_pos.y);
    //printf("distance : %d\n",distance);
    return ( distance > 5 );
}

void pre_compute_resize(t_game *game)
{
    int i = 0;
    t_vector3d v_right;
    t_vector3d v_ray_dir;
    t_vector3d v_player_to_camera_plane;
    float ca;
    //printf("half_width : %f\n", halfWidth);
    v_right = vec_rotate(game->player.direction, 90);
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
    while(i < RES_X)
    {
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[i]));
        ca = vec_angle(v_ray_dir, game->player.direction);
        game->fisheye_resize[i] = cosf(ca);
        game->fisheye_resize_wall[i] = cosf(ca);
        i++;
    }
}

void    render_fps(t_game *game)
{
    int line_height;
    t_collision collision;
    t_vector3d line_pos;
    t_vector3d v_ray_dir;
    t_wall_task     wall_task;
    
    line_pos.y = game->camera.half_res.y;
    line_pos.x = 0;
    int i = 0;
    pthread_mutex_lock(&game->queue_rights);
    game->task_count = 0;
    game->task_done = 0;
    game->render_finished = 0;
    pthread_mutex_unlock(&game->queue_rights); 
    while(line_pos.x < RES_X)
    {
        // v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[ (int) line_pos.x]));
        // v_ray_dir = vec_normalize(v_ray_dir);
        v_ray_dir = vec_rotate_rad(game->player.direction, game->ray_angle[(int)line_pos.x]);
        // v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[ (int) line_pos.x]));
        // v_ray_dir = vec_normalize(v_ray_dir);
        // v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[ (int) line_pos.x]));
        // v_ray_dir = vec_normalize(v_ray_dir);
        
        collision = cast_2D_ray(game, v_ray_dir);
        
        collision.distance  = collision.distance * game->fisheye_resize_wall[  (int) line_pos.x];
        // collision.distance  = collision.distance * game->fisheye_resize_wall[  (int) line_pos.x];
        line_height = game->wall_height  * game->camera.proj_plane_distance / (collision.distance);
        // line_pos.y = (game->camera.plane_center.y) + line_height / 2;
        
        // player_to_midwall.x =  collision.distance; 
        // player_to_midwall.y = game->wall_height / 2 - game->player.pos3d.z;
        // player_to_midwall = vec_normalize(player_to_midwall);
        // line_pos.y = (game->camera.plane_center.y) - player_to_midwall.y * game->camera.proj_plane_distance + line_height / 2;
        // printf("offset : %f \n", player_to_midwall.y * game->camera.proj_plane_distance);
        line_pos.y = (game->camera.plane_center.y) + ((int) line_height >> 1);

        wall_task.collision = collision;
        wall_task.line_height = line_height;  
        wall_task.line_pos = line_pos; 
        wall_task.v_ray_dir = v_ray_dir;
            
                
        submit_task_wall(game, wall_task);
        // wall_render(game, collision, line_pos, line_height);
        // pre_compute_rows_dist(game, line_pos, line_height, game->fisheye_resize[(int)  line_pos.x]);
        // render_floor(game, v_ray_dir, line_pos);
        // render_roof(game, v_ray_dir, line_pos, line_height);
        line_pos.x++;
        i++;
    }
    int all_tasks_ended = 0;
    while(1)
    {
        pthread_mutex_lock(&game->queue_rights);
        if(game->task_done >= RES_X - 1)
            all_tasks_ended = 1;
        pthread_mutex_unlock(&game->queue_rights);      
        if(all_tasks_ended)
            break;
    }
    // printf("out of loop\n");
    //close_window(game);
    // if(game->frame_count > 5)
    //     exit(0);
}
