/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_angle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:30:20 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:40 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	vec_to_angle(double angle, t_vector3d *vector)
{
	double	magnitude;

	vector->x = cos(angle);
	vector->y = sin(angle);
	magnitude = sqrt(pow(vector->x, 2) + pow(vector->y, 2));
	vector->x /= magnitude;
	vector->y /= magnitude;
}
