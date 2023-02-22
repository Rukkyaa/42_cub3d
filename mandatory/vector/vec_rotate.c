/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:14:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/22 14:15:00 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vec_rotate(t_vector vector, float angle)
{
	t_vector	output;
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
	return (output);
}
