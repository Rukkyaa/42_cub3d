/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotate_rad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:45:49 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 15:10:56 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_rotate_rad(t_vector3d vector, float angle)
{
	float	cosine;
	float	sine;
	float	x;
	float	y;

	cosine = cosf(angle);
	sine = sinf(angle);
	x = vector.x * cosine - vector.y * sine;
	y = vector.x * sine + vector.y * cosine;
	vector.x = x;
	vector.y = y;
	return(vector);
}
