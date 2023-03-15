/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/03/15 17:49:42 by teliet           ###   ########.fr       */
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

    while(i < RES_Y)
    {
        v3d_intersect_point = vec_sum(game->player.pos, vec_scalar_mult(v_ray_dir,  game->row_dist[i]));
        img_pix_put(&game->fps_img, line_pos.x, i, get_floor_color(game, v3d_intersect_point, &game->texture.ground));
        i++;
    }
}

void    render_roof(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos, float line_height)
{
    t_vector3d v3d_intersect_point;
    int i = 0;

    if(line_pos.x < 224)
        i = 224;

    while(i < line_pos.y - line_height)
    {
        v3d_intersect_point = vec_sum(game->player.pos, vec_scalar_mult(v_ray_dir,game->row_dist[i]));
        img_pix_put(&game->fps_img, line_pos.x, i, get_floor_color(game, v3d_intersect_point, &game->texture.roof));
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
    t_vector3d v_player_to_camera_plane;
    float ca;
    float angle_resize;;
    //printf("half_width : %f\n", halfWidth);
    v_right  = vec_normalize(game->camera.plane);
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
    line_pos.y = game->camera.half_res.y;
    while(i < RES_X)
    {
        printf("pre_compute %d\n", i);
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[i]));
        ca = vec_angle(v_ray_dir, game->player.direction);
        game->fisheye_resize[i] = cosf(ca);
        game->fisheye_resize_wall[i] = cosf(ca) * 64;
        i++;
    }
    
}

void    render_fps(t_game *game)
{
    int i = 0;
    float line_height;
    t_collision collision;
    t_vector3d v_right;
    t_vector3d line_pos;
    t_vector3d v_ray_dir;
    t_vector3d v_ray_dir2;
    t_vector3d v_player_to_camera_plane;
    float ca;
    float angle_resize;;
    //printf("half_width : %f\n", halfWidth);
    v_right  = vec_normalize(game->camera.plane) ;
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
    line_pos.y = game->camera.half_res.y;
    while(i < RES_X)
    {
        // offset = ((2.0f * (float) line_pos.x / (RES_X - 1.0f)) - 1.0f) * halfWidth;
        // // printf("offset : %f\n", offset);
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[i]));
        v_ray_dir = vec_normalize(v_ray_dir);
        // printf("angle : %f\n", angle_between_vectors(v_ray_dir, game->player.direction));
        // printf("%d : ", line_pos.x);
        // print_vector3d2D(&v_ray_dir, "raycast dir");
        collision = cast_2D_ray(game, v_ray_dir);
        // printf("distance : %f \n", collision.distance);
        // ca = vec_angle(v_ray_dir, game->player.direction);
        // angle_resize = cosf(ca);
        // collision.distance  = collision.distance * 64 * angle_resize;
        collision.distance  = collision.distance * game->fisheye_resize_wall[i];
        line_height = game->wall_height  * game->camera.proj_plane_distance / (collision.distance);
        //game->camera.plane_center.y = game->camera.half_res.y * ( 1 + ( game->wall_height - game->player.pos3d.z) / game->wall_height);
        line_pos.y = (game->camera.plane_center.y) + line_height / 2;
        line_pos.x = i;
        // printf("orientation : %c\n", collision.orientation);
            //draw_filled_circle(&game->fps_img, get_vector3d(1000, 400), line_height, PALE_BLUE);
        // if ((int) collision.point.x % 64 < 2  || (int) collision.point.y % 64 < 2) // 64 - (int) collision.point.x % 64 < 2 || 64 - (int) collision.point.y % 64 < 2
        //basic_render(game, collision, line_pos, line_height);
		
        wall_render(game, collision, line_pos, line_height);
        pre_compute_rows_dist(game, v_ray_dir2, line_pos, line_height, game->fisheye_resize[i]);
        render_floor(game, v_ray_dir, line_pos);
        render_roof(game, v_ray_dir, line_pos, line_height);
        i++;
    }
    //draw_line_dda(&game->debug_img, vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, halfWidth))),  vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, -halfWidth))), BLACK_PIXEL);
}
