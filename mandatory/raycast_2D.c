/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:15:48 by teliet            #+#    #+#             */
/*   Updated: 2023/05/09 10:10:31 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_circle_relative_tile_pos(t_game *game, t_vector point)
{
	point = vec_scalar_mult(point, 64);
	point = vec_sum(point, game->player.pos);
}

char	get_collision_orientation(char last_step, t_vector v_step)
{
	if (last_step == 'x')
	{
		if (v_step.x == 1)
			return ('W');
		else
			return ('E');
	}
	else
	{
		if (v_step.y == 1)
			return ('N');
		else
			return ('S');
	}
}

double	get_texture_x(char last_step, t_vector v_collision_point,
		t_vector v_map_check)
{
	if (last_step == 'x')
		return (v_collision_point.y - v_map_check.y * 64);
	else
		return (v_collision_point.x - v_map_check.x * 64);
}
