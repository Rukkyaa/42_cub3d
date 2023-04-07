/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:28:05 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 15:10:02 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	vec_distance(t_vector3d vec1, t_vector3d vec2)
{
	double	dist;

	dist = sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y)
			* (vec1.y - vec2.y));
	return (dist);
}

double vec3d_distance(t_vector3d vec1, t_vector3d vec2) 
{
    double dx = vec2.x - vec1.x;
    double dy = vec2.y - vec1.y;
    double dz = vec2.z - vec1.z;
    
    return sqrt(dx * dx + dy * dy + dz * dz);
}