/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:20:57 by teliet            #+#    #+#             */
/*   Updated: 2023/02/17 12:10:27 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

// void	rotate(t_vector *vector, float angle)
// {
// 	// Convert the angle from degrees to radians
// 	angle = angle * M_PI / 180.0f;

// 	// Calculate the sine and cosine of the angle
// 	float cosine = cosf(angle);
// 	float sine = sinf(angle);

// 	// Rotate the vector using the rotation matrix
// 	float x = vector->x * cosine - vector->y * sine;
// 	float y = vector->x * sine + vector->y * cosine;

// 	// Update the vector with the rotated coordinates
// 	vector->x = x;
// 	vector->y = y;
// }

void	rotate(t_vector *vector, float angle)
{
    // printf("vector : %f-%f\n",vector->x, vector->y);
	// Convert the angle from degrees to radians
	angle = angle * M_PI / 180.0f;

	// Calculate the sine and cosine of the angle
	float cosine = cosf(angle);
	float sine = sinf(angle);

	// Rotate the vector using the rotation matrix
	float x = vector->x * cosine - vector->y * sine;
	float y = vector->x * sine + vector->y * cosine;

	// Update the vector with the rotated coordinates
	vector->x = x;
	vector->y = y;
    // printf("new vector : %f-%f\n",vector->x, vector->y);
}