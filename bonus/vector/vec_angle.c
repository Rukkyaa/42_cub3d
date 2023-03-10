/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:32:16 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:40 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int sign(double x)
{
    if (x < 0.0)
        return -1;
    else if (x > 0.0)
        return 1;
    else
        return 0;
}

double	vec_angle(t_vector3d v1, t_vector3d v2)
{
	double	dot_product;
	double	magnitude1;
	double	magnitude2;
	double	cos_theta;

	dot_product = v1.x * v2.x + v1.y * v2.y;
	magnitude1 = sqrtf(v1.x * v1.x + v1.y * v1.y);
	magnitude2 = sqrtf(v2.x * v2.x + v2.y * v2.y);
	
	// check for zero vectors
	if (magnitude1 == 0.0 || magnitude2 == 0.0)
		return 0.0;

	cos_theta = dot_product / (magnitude1 * magnitude2);

	// check for nearly perpendicular vectors
	if (fabs(cos_theta) > 1.0 - DBL_EPSILON)
		return acos(sign(dot_product) * 1.0);

	return acos(cos_theta) * sign(v1.x * v2.y - v1.y * v2.x);
}
