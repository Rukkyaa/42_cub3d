/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:15:48 by teliet            #+#    #+#             */
/*   Updated: 2023/02/27 15:00:44 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

// void	cast_2D_ray(t_game *game)
// {
// 	t_vector tile_coord = pixel_to_tile(game->player.pos);
// 	game->map[(int) game->player.current_tile.y][ (int) game->player.current_tile.x] = '0';
// 	game->map[(int) tile_coord.y][ (int) tile_coord.x] = 'P';
// 	game->player.current_tile = tile_coord;
// 	//draw_filled_square(game,  tile_coord.x * 64, tile_coord.y * 64, 64, 88888);
// }

void    print_circle_relative_tile_pos(t_game *game, t_vector point)
{
    point = vec_scalar_mult(point, 64);
    point = vec_sum(point, game->player.pos);
    draw_filled_circle(&game->img, point, 12, RED_PIXEL);   
}

// char get_collision_orientation(t_vector v_tile_coord, t_vector v_collision_coord)
// {
//     print_vector2D(&v_tile_coord, "v_tile_coord : ");
//     print_vector2D(&v_collision_coord, "v_collision_coord : ");
//     if(v_collision_coord.x < v_collision_coord.y)
//     {
//         if((int) (v_collision_coord.x / 64) == v_tile_coord.x)
//             return 'O';
//         else
//             return 'S';
//     }
//     if(v_collision_coord.x > v_collision_coord.y)
//     {
//         if((int) (v_collision_coord.x / 64)== v_tile_coord.x + 1)
//             return 'E';
//         else
//             return 'N';
//     }
// }

char get_collision_orientation(char last_step, t_vector v_step)
{
    // print_vector2D(&v_tile_coord, "v_tile_coord : ");
    // print_vector2D(&v_collision_coord, "v_collision_coord : ");
    if(last_step == 'x')
    {
        if(v_step.x == 1)
            return 'O';
        else
            return 'E';
    }
    else
    {
        if(v_step.y == 1)
            return 'N';
        else
            return 'S';
    }
}

double get_texture_x(char last_step, t_vector v_collision_point, t_vector v_map_check)
{
    if(last_step == 'x')
    {
        // printf("%f\n",v_collision_point.y - v_map_check.y  * 64);
        return (v_collision_point.y - v_map_check.y * 64);
    }
    else
    {
        //     vec_print(&v_collision_point, "v_collision_point");
        // vec_print(&v_map_check, "v_map_check");
        // printf("%f\n",v_collision_point.x - v_map_check.x * 64);
        return (v_collision_point.x - v_map_check.x * 64);
    }
}


t_collision	cast_2D_ray(t_game *game, t_vector direction)
{
	t_vector v_ray_dir = direction;
	t_vector v_step;
	t_vector v_ray_length_1D;
	t_vector v_map_check = pixel_to_tile(game->player.pos);
    t_vector collision_point;
    t_collision collision;
    char last_step;
    int i = 0; 
	//draw_filled_square(game,  tile_coord.x * 64, tile_coord.y * 64, 64, 88888);

	t_vector v_ray_unit_step;
	v_ray_unit_step.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x) * (v_ray_dir.y / v_ray_dir.x) );
	v_ray_unit_step.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y) * (v_ray_dir.x / v_ray_dir.y)) ;


    // printf(" \n --------------- \n Start raycast from : %f-%f\n",game->player.pos.x, game->player.pos.y);
    // printf("v_ray_unit_step : %f: %f\n",v_ray_unit_step.x, v_ray_unit_step.y);
    // printf("v_map_check : %f: %f\n",v_map_check.x, v_map_check.y);
    // printf("v_ray_dir : %f: %f\n",v_ray_dir.x, v_ray_dir.y);
    
	// Starting Conditions
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

    // printf("v_ray_length_1D : %f: %f\n",v_ray_length_1D.x, v_ray_length_1D.y);
    // print_circle_relative_tile_pos(game, vec_scalar_mult(v_ray_dir, v_ray_length_1D.y));
    // print_circle_relative_tile_pos(game, vec_scalar_mult(v_ray_dir, v_ray_length_1D.x));
    int tile_found = 0;
    float max_distance = MAX_DISTANCE;
    float distance = 0.0f;

    while(!tile_found )//&& distance < max_distance)
    {
        // printf(" \n --------------- \n");
        // printf("distance :%f\n",distance);
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
        // printf("distance :%f\n",distance);
        // printf("v_stepdistance : %f: %f\n",v_step.x, v_step.y);
        // printf("v_ray_dir : %f: %f\n",v_ray_dir.x, v_ray_dir.y);
        // printf("v_ray_length_1D : %f: %f\n",v_ray_length_1D.x, v_ray_length_1D.y);
        // printf("v_map_check : %f-%f\n",v_map_check.x, v_map_check.y);
        collision_point = vec_scalar_mult(v_ray_dir, distance * 64);
        // printf("collision_point : %f: %f\n",collision_point.x, collision_point.y);
       // collision_point = vec_mult(v_map_check, game->player.direction); 
        collision_point = vec_sum(collision_point, game->player.pos);
        // printf("collision_point : %f: %f\n",collision_point.x, collision_point.y);
        //draw_line_dda(&game->img,  game->player.pos, collision_point, RED_PIXEL);
        // draw_filled_circle(game,  collision_point, 10, WHITE_PIXEL);
        
        i++;
        if(tile_out_of_bound(v_map_check, game))
            break ;
        if(game->map[(int)v_map_check.y][(int)v_map_check.x] == '1')
        {
            tile_found = 1;
            // draw_filled_circle(game, collision_point, 12, WHITE_PIXEL);
        }
        else
        {
            //game->map[(int)v_map_check.y][(int)v_map_check.x] = 'B';
            // draw_filled_circle(game, collision_point, 8, BLACK_PIXEL);
        }
    }
    //  printf("distance :%f\n",distance);
   // draw_line(game,  game->player.pos, collision_point, 3, RED_PIXEL);
    collision.distance = distance;
    collision.orientation = get_collision_orientation(last_step, v_step);
    collision.point = collision_point;
    collision.x_pos_tex = get_texture_x(last_step, collision_point ,v_map_check);

    return ((collision));
}
