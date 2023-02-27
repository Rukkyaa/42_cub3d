/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_angle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:30:20 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:00:44 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	vec_to_angle(double angle, t_vector *vector)
{
	double	magnitude;

	vector->x = cos(angle);
	vector->y = sin(angle);
	magnitude = sqrt(pow(vector->x, 2) + pow(vector->y, 2));
	vector->x /= magnitude;
	vector->y /= magnitude;
}
