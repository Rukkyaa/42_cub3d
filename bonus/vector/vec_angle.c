/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:32:16 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/07 20:07:18 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	vec_angle(t_vector v1, t_vector v2)
{
	double	dot_product;
	double	magnitude1;
	double	magnitude2;
	double	cos_theta;

	dot_product = v1.x * v2.x + v1.y * v2.y;
	magnitude1 = sqrtf(v1.x * v1.x + v1.y * v1.y);
	magnitude2 = sqrtf(v2.x * v2.x + v2.y * v2.y);
	cos_theta = dot_product / (magnitude1 * magnitude2);
	if(v1.x * v2.y - v1.y * v2.x < 0)
		return - acosf(cos_theta);
	else
		return acosf(cos_theta);

}
