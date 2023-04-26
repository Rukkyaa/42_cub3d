/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:15:48 by teliet            #+#    #+#             */
/*   Updated: 2023/03/26 23:46:56 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void    print_circle_relative_tile_pos(t_game *game, t_vector3d point)
{
    point = vec_scalar_mult(point, 64);
    point = vec_sum(point, game->player.pos);
}

char get_collision_orientation(char last_step, t_vector3d v_step)
{
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

double get_texture_x(char last_step, t_vector3d v_collision_point, t_vector3d v_map_check)
{
    if(last_step == 'x')
        return (v_collision_point.y - v_map_check.y * 64);
    else
        return (v_collision_point.x - v_map_check.x * 64);
}

int	is_door(char c)
{
	return (c == 'D');
}

t_collision	cast_2D_ray(t_game *game, t_vector3d direction)
{
	t_vector3d v_ray_dir = direction;
	t_vector3d v_step;
	t_vector3d v_ray_length_1D;
	t_vector3d v_map_check = pixel_to_tile(game->player.pos);
    t_vector3d collision_point;
    t_collision collision;
    char last_step;
    int i = 0; 

	t_vector3d v_ray_unit_step;
	v_ray_unit_step.x = sqrt(1 + (v_ray_dir.y / v_ray_dir.x) * (v_ray_dir.y / v_ray_dir.x) );
	v_ray_unit_step.y = sqrt(1 + (v_ray_dir.x / v_ray_dir.y) * (v_ray_dir.x / v_ray_dir.y)) ;

    // Door handling
    t_vector3d door_intersection;

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
    int tile_found = 0;
    float distance = 0.0f;

    while(!tile_found )
    {
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
            v_map_check.y += v_step.y;
            distance = v_ray_length_1D.y;
            v_ray_length_1D.y += v_ray_unit_step.y;
        }
        collision_point = vec_scalar_mult(v_ray_dir, distance * 64);
        collision_point = vec_sum(collision_point, game->player.pos);
        
        i++;
        if(is_wall(game->map[(int)v_map_check.y][(int)v_map_check.x]))
        {
            tile_found = 1;
			get_wall(game, &collision, game->map[(int)v_map_check.y][(int)v_map_check.x]);
        }
        else if(is_door(game->map[(int)v_map_check.y][(int)v_map_check.x]))
        {
            if(last_step == 'y')
            {
                door_intersection.x = fmod(collision_point.x , 64) + 32 * (v_ray_dir.y / v_ray_dir.x);
                printf("ystep\n");
            }
            else 
            {
                door_intersection.y = collision_point.y + 32 * v_ray_dir.y / fabs(v_ray_dir.x);
            }
            if( ((int) door_intersection.y ) / 64 ==  v_map_check.y)
            {
                collision.x_pos_tex = ((int) door_intersection.y ) % 64;
                collision.distance = distance * 64 + sqrtf(32 * 32 + pow(v_ray_dir.y / v_ray_dir.x * 32, 2));
                collision.orientation = get_collision_orientation(last_step, v_step);
                collision.point = collision_point;
                tile_found = 1;
                get_wall(game, &collision, game->map[(int)v_map_check.y][(int)v_map_check.x]);
                return (collision);
            }
        }
    }
    collision.distance = distance * 64;
    collision.orientation = get_collision_orientation(last_step, v_step);
    collision.point = collision_point;
    collision.x_pos_tex = get_texture_x(last_step, collision_point ,v_map_check);
    return ((collision));
}
