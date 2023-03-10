/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotate_rad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:45:49 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:40 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	vec_rotate_rad(t_vector3d *vector, float angle)
{
	float	cosine;
	float	sine;
	float	x;
	float	y;

	cosine = cosf(angle);
	sine = sinf(angle);
	x = vector->x * cosine - vector->y * sine;
	y = vector->x * sine + vector->y * cosine;
	vector->x = x;
	vector->y = y;
}
