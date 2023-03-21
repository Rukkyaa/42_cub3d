/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/03/21 11:11:02 by teliet           ###   ########.fr       */
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


int get_floor_color(t_game *game, t_vector3d intersection, t_img *img)
{
    t_vector3d v_tile;
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

    while(i < RES_Y)
    {
        pixel_color =  get_floor_color(game, v3d_intersect_point, &game->texture.ground);
        v3d_intersect_point = vec_sum(game->player.pos, vec_scalar_mult(v_ray_dir,  game->row_dist[i]));
        pixel_color = add_shade(pixel_color, fmax(1 -  vec_distance(game->player.pos, v3d_intersect_point) / 1000, 0)); 
        img_pix_put(&game->fps_img, line_pos.x, i, pixel_color);
        i++;
    }
}

void    render_roof(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos, float line_height)
{
    t_vector3d v3d_intersect_point;
    int i = 0;
    int pixel_color;

    if(line_pos.x < 224)
        i = 224;

    while(i < line_pos.y - line_height)
    {
        pixel_color = get_floor_color(game, v3d_intersect_point, &game->texture.roof);
        v3d_intersect_point = vec_sum(game->player.pos, vec_scalar_mult(v_ray_dir,game->row_dist[i]));
        pixel_color = add_shade(pixel_color, fmax(1 -  vec_distance(game->player.pos, v3d_intersect_point) / 1000, 0)); 
        // pixel_color = add_shade(pixel_color, fmax(1 -  vec_distance(game->player.pos, v3d_intersect_point) / 1000, 0)); 
        img_pix_put(&game->fps_img, line_pos.x, i, pixel_color);
        i++;
    }
}


void    pre_compute_rows_dist(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos, float line_height, float resize)
{
    int i = 0;
    float dist;

    // roof
    while(i < line_pos.y - line_height)
    {
        dist = ((game->wall_height - game->player.pos3d.z ) * game->camera.proj_plane_distance) / (float) (game->camera.plane_center.y - i);
        dist /= resize;
        game->row_dist[i] = dist;
        i++;
    }   
    // floor
    i = line_pos.y;
    while(i < RES_Y)
    {
        dist = (game->player.pos3d.z  * game->camera.proj_plane_distance) / (float) (i - game->camera.plane_center.y);
        dist /= resize;
        game->row_dist[i] = dist;
        i++;
    }
}

void pre_compute_resize(t_game *game)
{
    int i = 0;
    float line_height;
    t_collision collision;
    t_vector3d v_right;
    t_vector3d line_pos;
    t_vector3d v_ray_dir;
    t_vector3d v_ray_dir2;
    t_vector3d player_to_midwall;
    t_vector3d v_player_to_camera_plane;
    float ca;
    float angle_resize;;
    //printf("half_width : %f\n", halfWidth);
    v_right  = vec_normalize(game->camera.plane);
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
    line_pos.y = game->camera.half_res.y;
    while(i < RES_X)
    {
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[i]));
        ca = vec_angle(v_ray_dir, game->player.direction);
        game->fisheye_resize[i] = cosf(ca);
        game->fisheye_resize_wall[i] = cosf(ca) * 64;
        i++;
    }
    
}

void    render_fps(t_game *game)
{
    float line_height;
    t_collision collision;
    t_vector3d v_right;
    t_vector3d line_pos;
    t_vector3d v_ray_dir;
    t_vector3d v_player_to_camera_plane;
    t_vector3d player_to_midwall;
    
    v_right  = vec_normalize(game->camera.plane) ;
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
    line_pos.y = game->camera.half_res.y;
    line_pos.x = 0;
    while(line_pos.x < RES_X)
    {
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[ (int) line_pos.x]));
        v_ray_dir = vec_normalize(v_ray_dir);
        
        collision = cast_2D_ray(game, v_ray_dir);
        
        collision.distance  = collision.distance * game->fisheye_resize_wall[  (int) line_pos.x];
        line_height = game->wall_height  * game->camera.proj_plane_distance / (collision.distance);
        // line_pos.y = (game->camera.plane_center.y) + line_height / 2;
        
        // player_to_midwall.x =  collision.distance; 
        // player_to_midwall.y = game->wall_height / 2 - game->player.pos3d.z;
        // player_to_midwall = vec_normalize(player_to_midwall);
        // line_pos.y = (game->camera.plane_center.y) - player_to_midwall.y * game->camera.proj_plane_distance + line_height / 2;
       // printf("offset : %f \n", player_to_midwall.y * game->camera.proj_plane_distance);
        line_pos.y = (game->camera.plane_center.y) + line_height / 2;


        wall_render(game, collision, line_pos, line_height);
        pre_compute_rows_dist(game, v_ray_dir, line_pos, line_height, game->fisheye_resize[(int)  line_pos.x]);
        render_floor(game, v_ray_dir, line_pos);
        render_roof(game, v_ray_dir, line_pos, line_height);
        line_pos.x++;
    }
}
