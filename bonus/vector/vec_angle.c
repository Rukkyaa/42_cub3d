/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:32:16 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:00:44 by teliet           ###   ########.fr       */
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
	magnitude1 = sqrt(v1.x * v1.x + v1.y * v1.y);
	magnitude2 = sqrt(v2.x * v2.x + v2.y * v2.y);
	cos_theta = dot_product / (magnitude1 * magnitude2);
	return (acosf(cos_theta));
}
