/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/03/10 15:34:53 by theo             ###   ########.fr       */
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

    v_tile.x = (int) intersection.x / 64;
    v_tile.y = (int) intersection.y / 64;

    // to do : get texture of the specific tile hit
    v_texture_pos.x = fmod(intersection.x, game->texture.ground.width);
    v_texture_pos.y = fmod(intersection.y,  game->texture.ground.heigth);
    // vec_print(&v_texture_pos, "v_texture_pos");
    return(img_pix_read(img, v_texture_pos.x, v_texture_pos.y));
}

void    render_floor_col(t_game *game, t_vector3d v_ray_dir, t_vector3d line_pos)
{
    t_vector3d v3d_ray_dir;
    t_vector3d v3d_intersect_point;
    t_vector3d v_intersect_point;
    int i = line_pos.y;
    float plane_height = game->camera.proj_plane_height;
    float vertical_ray_increment = (float) plane_height * 2.27 * 1.25 / (float) RES_Y; //(((float) (RES_Y - line_pos.y) / (float) RES_Y) * plane_height) / (RES_Y - line_pos.y) ;
    // printf( "plane_height : %f\n", plane_height);
    // printf( "plane_width : %f\n", plane_halfwidth * 2);
    // printf( "vertical_ray_increment : %f\n", vertical_ray_increment);

    v3d_ray_dir.x = v_ray_dir.x;
    v3d_ray_dir.y = v_ray_dir.y;

    game->player.pos3d.x = game->player.pos.x;
    game->player.pos3d.y = game->player.pos.y;
    t_vector3d test;

    test.x = v3d_ray_dir.x ;
    test.y = v3d_ray_dir.y;
    // test.z = -64;
    while(i < RES_Y)
    {
        v3d_ray_dir.z = - ( i - RES_Y / 2.0f ) * vertical_ray_increment;
        //vec3_print(v3d_ray_dir, "v3d_ray_dir");
        // vec3_print(game->player.pos3d, "game->player.pos3d");
        v3d_intersect_point = get_floor_intersection(game->player.pos3d, v3d_ray_dir); //get_floor_intersection(game->player.pos3d, test);
        //distance = vec3d_distance(game->player.pos3d, v3d_intersect_point);
        // vec3_print(v3d_intersect_point, "v3d_intersect_point");
        v_intersect_point.x = v3d_intersect_point.x;
        v_intersect_point.y = v3d_intersect_point.y;
        // draw_line_dda(&game->debug_img, game->player.pos, vec_sum(game->player.pos, test), RED_PIXEL);
        // img_pix_put(&game->debug_img, v_intersect_point.x, v_intersect_point.y, GREEN_PIXEL);
        //draw_filled_circle(&game->debug_img, v_intersect_point, 10, BLUE_PIXEL);
        img_pix_put(&game->fps_img, line_pos.x, RES_Y - i, get_floor_color(game, v3d_intersect_point,  &game->texture.roof));
        img_pix_put(&game->fps_img, line_pos.x, i, get_floor_color(game, v3d_intersect_point, &game->texture.ground));
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
    //printf("half_width : %f\n", halfWidth);
    v_right  = vec_normalize(game->camera.plane) ;
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
    line_pos.y = HALF_RES_Y;
    while(i < RES_X)
    {
        // offset = ((2.0f * (float) line_pos.x / (RES_X - 1.0f)) - 1.0f) * halfWidth;
        // // printf("offset : %f\n", offset);
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, game->ray_offset[i]));
        v_ray_dir2 = vec_copy(v_ray_dir);
        v_ray_dir = vec_normalize(v_ray_dir);
        // printf("angle : %f\n", angle_between_vectors(v_ray_dir, game->player.direction));
        // printf("%d : ", line_pos.x);
        // print_vector3d2D(&v_ray_dir, "raycast dir");
        collision = cast_2D_ray(game, v_ray_dir);
        // printf("distance : %d \n", distance);
        ca = vec_angle(v_ray_dir, game->player.direction);
        collision.distance  = collision.distance * cosf(ca);
        line_height = ( 64 / collision.distance ) * game->camera.proj_plane_distance;
        line_pos.y = HALF_RES_Y + line_height / 2;
        line_pos.x = i;
        // printf("orientation : %c\n", collision.orientation);
            //draw_filled_circle(&game->fps_img, get_vector3d(1000, 400), line_height, PALE_BLUE);
        // if ((int) collision.point.x % 64 < 2  || (int) collision.point.y % 64 < 2) // 64 - (int) collision.point.x % 64 < 2 || 64 - (int) collision.point.y % 64 < 2
        //basic_render(game, collision, line_pos, line_height);
		
        wall_render(game, collision, line_pos, line_height);
        render_floor_col(game, v_ray_dir2, line_pos);
        i++;
    }
    //draw_line_dda(&game->debug_img, vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, halfWidth))),  vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, -halfWidth))), BLACK_PIXEL);
}
