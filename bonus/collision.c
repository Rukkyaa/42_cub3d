/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:56:35 by teliet            #+#    #+#             */
/*   Updated: 2023/02/27 18:28:29 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector	get_next_tile(t_game *game, t_vector direction)
{
	t_vector v_ray_dir = direction;
	t_vector v_step;
	t_vector v_ray_length_1D;
	t_vector v_map_check = pixel_to_tile(game->player.pos);
    t_vector collision_point;
    char last_step;
    int i = 0; 
    int distance = 0;

	t_vector v_ray_unit_step;
	v_ray_unit_step.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x) * (v_ray_dir.y / v_ray_dir.x) );
	v_ray_unit_step.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y) * (v_ray_dir.x / v_ray_dir.y)) ;


	if (v_ray_dir.x < 0)
	{
		v_step.x = -1;
		v_ray_length_1D.x = (game->player.pos.x - tile_to_pixel(v_map_check).x ) / 64 * v_ray_unit_step.x; // v_ray_unit_step.x; //
	}
	else
	{
		v_step.x = 1;
		v_ray_length_1D.x = (tile_to_pixel(v_map_check).x + 64 - game->player.pos.x ) / 64 * v_ray_unit_step.x; // v_ray_unit_step.x; 
	}
	if (v_ray_dir.y < 0)
	{
		v_step.y = -1;
		v_ray_length_1D.y =  (game->player.pos.y - tile_to_pixel(v_map_check).y) / 64 * v_ray_unit_step.y; //v_ray_unit_step.y;
	}
	else
	{
		v_step.y = 1;
		v_ray_length_1D.y = (tile_to_pixel(v_map_check).y + 64 - game->player.pos.y) / 64  * v_ray_unit_step.y; //v_ray_unit_step.y; 
	}

    if(v_ray_length_1D.x < v_ray_length_1D.y)
    {
        last_step = 'x';
        v_map_check.x += v_step.x;
        distance = v_ray_length_1D.x;
        v_ray_length_1D.x += v_ray_unit_step.x;
    }
    else
    {
        last_step = 'y';
        // printf("v_map_check : %f: %f\n",v_map_check.x, v_map_check.y);
        v_map_check.y += v_step.y;
        // printf("v_map_check : %f: %f\n",v_map_check.x, v_map_check.y);
        distance = v_ray_length_1D.y;
        v_ray_length_1D.y += v_ray_unit_step.y;
    }
    // if(game->map[(int)v_map_check.y][(int)v_map_check.x] == '1')
    // {
    //     // tile_found = 1;
    //     // draw_filled_circle(game, collision_point, 12, WHITE_PIXEL);
    // }
    // else
    // {
    //     game->map[(int)v_map_check.y][(int)v_map_check.x] = 'B';
    //     // draw_filled_circle(game, collision_point, 8, BLACK_PIXEL);
    // }
    collision_point = vec_scalar_mult(v_ray_dir, distance * 64);
    collision_point = vec_sum(collision_point, game->player.pos);
    // printf("collision point : %f|%f\n", collision_point.x,collision_point.y);
    // draw_line_dda(&game->img,  game->player.pos, collision_point, RED_PIXEL);
    return(vec_sum(v_map_check, vec_scalar_mult(pixel_to_tile(game->player.pos), -1)));
}