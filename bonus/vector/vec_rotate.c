/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:14:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 15:11:10 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_rotate(t_vector3d vector, float angle)
{
	t_vector3d	output;
	float		cosine;
	float		sine;
	float		x;
	float		y;

	angle = angle * M_PI / 180.0f;
	cosine = cosf(angle);
	sine = sinf(angle);
	x = vector.x * cosine - vector.y * sine;
	y = vector.x * sine + vector.y * cosine;
	output.x = x;
	output.y = y;
	output.z = vector.z;
	return (output);
}
