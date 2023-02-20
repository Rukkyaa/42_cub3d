/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:20:57 by teliet            #+#    #+#             */
/*   Updated: 2023/02/20 17:02:12 by teliet           ###   ########.fr       */
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

int pixel_out_of_bound(float x, float y)
{
    t_vector pixel_coord;
    

    pixel_coord.x = x;
    pixel_coord.y = y;
    return(!( 0 <= pixel_coord.x  && pixel_coord.x < 512 && 0 <= pixel_coord.y  && pixel_coord.y < 512));
}

int tile_out_of_bound(t_vector tile_coord)
{
    return (!( 0 <= tile_coord.x  && tile_coord.x < 8 && 0 <= tile_coord.y  && tile_coord.y < 8));
}

t_vector tile_to_pixel(t_vector tile_coord)
{
    t_vector pixel_coord;

    pixel_coord.x = (int) (tile_coord.x * 64.0f);
    pixel_coord.y = (int) (tile_coord.y * 64.0f);
    return(pixel_coord);
}

t_vector pixel_to_tile(t_vector vector)
{
    t_vector tile_coord;

    tile_coord.x = (int) (vector.x / 64.0f);
    tile_coord.y = (int) (vector.y / 64.0f);
    return(tile_coord);
}

t_vector vec_sum(t_vector vec1, t_vector vec2)
{
    t_vector sum;

    sum.x = vec1.x + vec2.x;
    sum.y = vec1.y + vec2.y;
    return(sum);
}

t_vector vec_mult(t_vector vec1, t_vector vec2)
{
    t_vector mult;

    mult.x = vec1.x * vec2.x;
    mult.y = vec1.y * vec2.y;
    return(mult);
}

t_vector vec_scalar_mult(t_vector vec1, double i)
{
    t_vector mult;

    mult.x = vec1.x * i;
    mult.y = vec1.y * i;
    return(mult);
}

void angle_to_vector(double angle, t_vector *vector) {
    // vector->x = cos(angle);
}

void vector_to_angle(double angle, t_vector *vector) {
    vector->x = cos(angle);
    vector->y = sin(angle);
    
    // normalize the vector
    double magnitude = sqrt(pow(vector->x, 2) + pow(vector->y, 2));
    vector->x /= magnitude;
    vector->y /= magnitude;
}

void    print_vector2D(t_vector *vector, char *name)
{
    printf("-----------------------------------------------\n");
    printf("| %s : x : %f | y : %f   |\n", name, vector->x, vector->y);
    printf("-----------------------------------------------\n");
}

void	rotate_rad(t_vector *vector, float angle)
{

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

t_vector	rotate2(t_vector vector, float angle)
{
    // printf("vector : %f-%f\n",vector->x, vector->y);
	// Convert the angle from degrees to radians
    t_vector    output;
	angle = angle * M_PI / 180.0f;

	// Calculate the sine and cosine of the angle
	float cosine = cosf(angle);
	float sine = sinf(angle);

	// Rotate the vector using the rotation matrix
	float x = vector.x * cosine - vector.y * sine;
	float y = vector.x * sine + vector.y * cosine;

	// Update the vector with the rotated coordinates
	output.x = x;
	output.y = y;
    // printf("new vector : %f-%f\n",vector->x, vector->y);
    return(output);
}

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