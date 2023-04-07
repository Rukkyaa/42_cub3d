/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/04/07 20:27:10 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d get_floor_intersection(t_vector3d position, t_vector3d direction) {
    t_vector3d intersection;
    
    double t = -position.z / direction.z;
    intersection.x = position.x + t * direction.x;
    intersection.y = position.y + t * direction.y;
    intersection.z = 0;
    
    return intersection;
}


int get_floor_color(t_vector3d intersection, t_img *img)
{
	t_vector3d v_texture_pos;

    // v_tile.x = (int) intersection.x / 64;
    // v_tile.y = (int) intersection.y / 64;

    // to do : get texture of the specific tile hit
    v_texture_pos.x = fmod(intersection.x, 64); /// 64;
    v_texture_pos.y = fmod(intersection.y,  64); // / 64;
    // vec_print(&v_texture_pos, "v_texture_pos");
    //return(sample_img(img, v_texture_pos.x, v_texture_pos.y));
    return(img_pix_read(img, v_texture_pos.x, v_texture_pos.y));
}

void    render_floor(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos)
{
    t_vector3d v3d_intersect_point;
    int i = line_pos.y;
    int pixel_color;
    int shade = 1;
    float distance;
    unsigned int *img_addr;

    img_addr = ( unsigned int *)img_get_addr(&game->fps_img, line_pos.x, i);
    while(i < RES_Y)
    {
        v3d_intersect_point = vec_sum(game->player.pos, vec_scalar_mult(v_ray_dir,  game->row_dist[(int)line_pos.x][i]));
        // printf("read dist\n");
        pixel_color =  get_floor_color(v3d_intersect_point, &game->texture.ground);
            // pixel_color = add_shade(pixel_color, 0.5  * 255); 
        if(HD && shade)
        {
            distance = vec_distance(game->player.pos, v3d_intersect_point);
            if(distance > 320)
                pixel_color = add_shade(pixel_color, fmin(fmax(1 - (distance  - 320 ) / 512, 0), 1) * 255); 
            else
                shade = 0;
        }
        

        *img_addr = pixel_color;  
        // img_pix_put(&game->fps_img, line_pos.x, i, pixel_color);
        // printf("pix_put\n");
        img_addr += RES_X;
        i++;
    }
}

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

int get_roof_color(t_game *game, t_vector3d intersection, t_img *img)
{
	t_vector3d v_texture_pos;
	t_vector3d v_tile;

    v_tile.x = (int) intersection.x / 64;
    v_tile.y = (int) intersection.y / 64;
    if(game->map[(int)v_tile.y][(int)v_tile.x] == 'E')
        return(0xff001010);
    // to do : get texture of the specific tile hit
    v_texture_pos.x = fmod(intersection.x, 64); /// 64;
    v_texture_pos.y = fmod(intersection.y,  64); // / 64;
    // vec_print(&v_texture_pos, "v_texture_pos");
    //return(sample_img(img, v_texture_pos.x, v_texture_pos.y));
    return(img_pix_read(img, v_texture_pos.x, v_texture_pos.y));
}

void    render_roof(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos, float line_height)
{
    t_vector3d v3d_intersect_point;
    int i = line_pos.y - line_height - 1;
    int pixel_color;
    int shade = 1;
    int min = 0;
    float distance ;
    unsigned int *img_addr;


    if(line_pos.x < 224)
        min = 224;

    img_addr = ( unsigned int *)img_get_addr(&game->fps_img, line_pos.x, i);

    while(i >= min)
    {
        
        v3d_intersect_point = vec_sum(game->player.pos, vec_scalar_mult(v_ray_dir,game->row_dist[(int)line_pos.x][i]));
        pixel_color = get_roof_color(game, v3d_intersect_point, &game->texture.roof);
        if(HD && shade)
        {
            distance = vec_distance(game->player.pos, v3d_intersect_point);
            if(distance > 320)
                pixel_color = add_shade(pixel_color, fmin(fmax(1 - (distance  - 320 ) / 512, 0), 1) * 255); 
            else
                shade = 0;
        }
        *img_addr = pixel_color; 
        // pixel_color = add_shade(pixel_color, fmax(1 -  vec_distance(game->player.pos, v3d_intersect_point) / 1000, 0)); 
        //img_pix_put(&game->fps_img, line_pos.x, i, pixel_color);
        img_addr -= RES_X;
        i--;
    }

}


void    pre_compute_rows_dist(t_game *game, t_vector3d line_pos, float line_height, float resize)
{
    int i = 0;
    float dist;

    // roof
    while(i < line_pos.y - line_height)
    {
        dist = ((game->wall_height - game->player.pos3d.z ) * game->camera.proj_plane_distance) / (float) (game->camera.plane_center.y - i);
        dist /= resize;
        game->row_dist[(int)line_pos.x][i] = dist;
        i++;
    }   
    // floor
    i = line_pos.y;
    while(i < RES_Y)
    {
        dist = (game->player.pos3d.z  * game->camera.proj_plane_distance) / (float) (i - game->camera.plane_center.y);
        dist /= resize;
        game->row_dist[(int)line_pos.x][i] = dist;
        i++;
    }
}

void pre_compute_resize(t_game *game)
{
    int i = 0;
    t_vector3d v_right;
    t_vector3d v_ray_dir;
    t_vector3d v_player_to_camera_plane;
    float ca;
    //printf("half_width : %f\n", halfWidth);
    v_right  = vec_normalize(game->camera.plane);
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
    // printf("Rendering frame #%d\n", game->frame_count);
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
