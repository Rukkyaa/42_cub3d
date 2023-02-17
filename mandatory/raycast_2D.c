/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:15:48 by teliet            #+#    #+#             */
/*   Updated: 2023/02/17 16:31:32 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	cast_2D_ray(t_game *game)
// {
// 	t_vector tile_coord = pixel_to_tile(game->player.pos);
// 	game->map[(int) game->player.current_tile.y][ (int) game->player.current_tile.x] = '0';
// 	game->map[(int) tile_coord.y][ (int) tile_coord.x] = 'P';
// 	game->player.current_tile = tile_coord;
// 	//draw_filled_square(game,  tile_coord.x * 64, tile_coord.y * 64, 64, 88888);
// }


void	cast_2D_ray(t_game *game)
{
	t_vector v_ray_dir = game->player.direction;
	t_vector v_step;
	t_vector v_ray_length_1D;
	t_vector v_map_check = pixel_to_tile(game->player.pos);
	//draw_filled_square(game,  tile_coord.x * 64, tile_coord.y * 64, 64, 88888);

	t_vector v_ray_unit_step;
	v_ray_unit_step.x = sqrt(1 + (game->player.direction.y / game->player.direction.x) * (game->player.direction.y / game->player.direction.x) );
	v_ray_unit_step.y = sqrt(1 + (game->player.direction.x / game->player.direction.y) * (game->player.direction.x / game->player.direction.y)) ;


    printf(" \n --------------- \n Start raycast from : %f-%f\n",game->player.pos.x, game->player.pos.y);
    printf("v_ray_unit_step : %f-%f\n",v_ray_unit_step.x, v_ray_unit_step.y);
    
	// Starting Conditions
	if (v_ray_dir.x < 0)
	{
		v_step.x = -1;
		v_ray_length_1D.x = v_ray_unit_step.x; //(vRayStart.x - float(vMapCheck.x)) * vRayUnitStepSize.x;
	}
	else
	{
		v_step.x = 1;
		v_ray_length_1D.x = v_ray_unit_step.x; //(float(vMapCheck.x + 1) - vRayStart.x) * vRayUnitStepSize.x;
	}
	if (v_ray_dir.y < 0)
	{
		v_step.y = -1;
		v_ray_length_1D.y = v_ray_unit_step.y; //(vRayStart.y - float(vMapCheck.y)) * vRayUnitStepSize.y;
	}
	else
	{
		v_step.y = 1;
		v_ray_length_1D.y =  v_ray_unit_step.y;// (float(vMapCheck.y + 1) - vRayStart.y) * vRayUnitStepSize.y;
	}

    int tile_found = 0;
    float max_distance = 100.0f;
    float distance = 0.0f;

    while(!tile_found && distance < max_distance)
    {
        if(v_ray_length_1D.x > v_ray_length_1D.y)
        {
            v_map_check.x += v_step.x;
            v_ray_length_1D.x += v_ray_unit_step.x;
            distance = v_ray_length_1D.x;
        }
        else
        {
            v_map_check.y += v_step.y;
            v_ray_length_1D.y += v_ray_unit_step.y;
            distance = v_ray_length_1D.y;
        }
        printf("distance :%f\n",distance);
        printf("v_ray_length_1D : %f-%f\n",v_ray_length_1D.x, v_ray_length_1D.y);
        t_vector collision_point = vec_scalar_mult(v_ray_dir, distance );
        collision_point = vec_sum(collision_point, game->player.pos);
        printf("collision_point : %f-%f\n",collision_point.x, collision_point.y);
        printf("collision_point : %f-%f\n",collision_point.x, collision_point.y);
        draw_filled_circle(game,collision_point, 12, BLACK_PIXEL);
        // draw_line(game,  game->player.pos, vec_sum(collision_point, game->player.pos), 3, RED_PIXEL);
        // draw_filled_circle(game,  collision_point, 10, WHITE_PIXEL);
        if(!tile_out_of_bound(v_map_check))
            return ;
        if(game->map[(int)v_map_check.y][(int)v_map_check.x] == '1')
        {
            tile_found = 1;
        }
        else
            game->map[(int)v_map_check.y][(int)v_map_check.x] = 'B';
    }
    // return (distance);
}