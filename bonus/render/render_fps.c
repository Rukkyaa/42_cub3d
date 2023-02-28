/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/02/28 11:06:09 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    basic_render(t_game *game, t_collision collision, t_vector line_pos, double line_height)
{
    if(collision.orientation == 'S' || collision.orientation == 'N')
        draw_vertical_line_2(&game->fps_img, line_pos,  line_height, PALE_BLUE);
    else
        draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE_SHADED);  
}

void wall_render(t_game *game, t_collision collision, t_vector line_pos, double line_height)
{
    int i = -1;
    int x_text = 0;
    int y_text = 0;
    int pixel_color;

	while (++i < line_pos.y)
		img_pix_put(&game->fps_img, line_pos.x, i, 0x696969);
	i = 0;
    
    while(i < line_height)
    {
        x_text = (int) collision.x_pos_tex;
        y_text = (int) (((line_height - i) / line_height) * 64);
        pixel_color =  img_pix_read(&game->texture.wall, x_text, y_text) ;
        // printf("pixel %d %d : %ld\n", x_text, y_text, pixel_color);
        img_pix_put(&game->fps_img, line_pos.x, line_pos.y - i, pixel_color);
        i++;
    }
}

t_vector3d get_floor_intersection(t_vector3d position, t_vector3d direction) {
    t_vector3d intersection;
    
    double t = -position.z / direction.z;
    intersection.x = position.x + t * direction.x;
    intersection.y = position.y + t * direction.y;
    intersection.z = 0;
    
    return intersection;
}


int get_floor_color(t_game *game, t_vector3d intersection)
{
    t_vector v_tile;
    t_vector v_texture_pos;

    v_tile.x = (int) intersection.x / 64;
    v_tile.y = (int) intersection.y / 64;

    // to do : get texture of the specific tile hit
    v_texture_pos.x = fmod(intersection.x, 64);
    v_texture_pos.y = fmod(intersection.y, 64);
    // vec_print(&v_texture_pos, "v_texture_pos");
    return(img_pix_read(&game->texture.ground, v_texture_pos.x, v_texture_pos.y));
}

void    render_floor_col(t_game *game, t_vector v_ray_dir, t_vector line_pos)
{
    t_vector3d v3d_ray_dir;
    t_vector3d v3d_intersect_point;
    t_vector v_intersect_point;
    int i = line_pos.y;
    float plane_height = game->camera.proj_plane_height;
    float vertical_ray_increment = (float) plane_height * 2.27 / (float) RES_Y; //(((float) (RES_Y - line_pos.y) / (float) RES_Y) * plane_height) / (RES_Y - line_pos.y) ;
    // printf( "plane_height : %f\n", plane_height);
    // printf( "plane_width : %f\n", plane_halfwidth * 2);
    // printf( "vertical_ray_increment : %f\n", vertical_ray_increment);

    v3d_ray_dir.x = v_ray_dir.x;
    v3d_ray_dir.y = v_ray_dir.y;

    game->player.pos3d.x = game->player.pos.x;
    game->player.pos3d.y = game->player.pos.y;
    t_vector test;

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
        // draw_line_dda(&game->img, game->player.pos, vec_sum(game->player.pos, test), RED_PIXEL);
        // img_pix_put(&game->img, v_intersect_point.x, v_intersect_point.y, GREEN_PIXEL);
        //draw_filled_circle(&game->img, v_intersect_point, 10, BLUE_PIXEL);
        img_pix_put(&game->fps_img, line_pos.x, i, get_floor_color(game, v3d_intersect_point));
        i++;
    }
    
}


void    render_fps(t_game *game)
{
    int i = 0;
    float line_height;
    t_collision collision;
    t_vector v_right;
    t_vector line_pos;
    t_vector v_ray_dir;
    t_vector v_ray_dir2;
    t_vector v_player_to_camera_plane;
    float halfWidth;
    float offset;
    halfWidth = game->camera.proj_plane_width / 2.0f;
    //printf("half_width : %f\n", halfWidth);
    v_right  = vec_normalize(vec_rotate(game->player.direction, 90)) ;
    v_player_to_camera_plane = vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance);
    line_pos.x = 0;
    line_pos.y = RES_Y / 2;
    while(i < RES_X)
    {
        offset = ((2.0f * (float) line_pos.x / (RES_X - 1.0f)) - 1.0f) * halfWidth;
        // printf("offset : %f\n", offset);
        v_ray_dir = vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, offset));
        v_ray_dir2= vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, offset));
        v_ray_dir = vec_normalize(v_ray_dir);
        // printf("angle : %f\n", angle_between_vectors(v_ray_dir, game->player.direction));
        // printf("%d : ", line_pos.x);
        // print_vector2D(&v_ray_dir, "raycast dir");
        collision = cast_2D_ray(game, v_ray_dir);
        // printf("distance : %d \n", distance);
        float ca = vec_angle(v_ray_dir, game->player.direction);
        collision.distance  = collision.distance * cosf(ca);
        line_height = ( 64 / collision.distance ) * game->camera.proj_plane_distance  ;
        line_pos.y = RES_Y / 2 + line_height / 2;
        render_floor_col(game, v_ray_dir2, line_pos);
        // printf("orientation : %c\n", collision.orientation);
            //draw_filled_circle(&game->fps_img, get_vector(1000, 400), line_height, PALE_BLUE);
        // if ((int) collision.point.x % 64 < 2  || (int) collision.point.y % 64 < 2) // 64 - (int) collision.point.x % 64 < 2 || 64 - (int) collision.point.y % 64 < 2
        //basic_render(game, collision, line_pos, line_height);
        wall_render(game, collision, line_pos, line_height);
        i++;
        line_pos.x+= RES_X / RES_X;
    }
    draw_line_dda(&game->img, vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, halfWidth))),  vec_sum(game->player.pos, vec_sum(v_player_to_camera_plane, vec_scalar_mult(v_right, -halfWidth))), BLACK_PIXEL);
}
