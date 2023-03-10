/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:31:04 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 15:34:53 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	vec_print(t_vector3d *vector, char *name)
{
	printf("-----------------------------------------------\n");
	printf("| %s : x : %f | y : %f   |\n", name, vector->x, vector->y);
	printf("-----------------------------------------------\n");
}

void	vec3_print(t_vector3d vector, char *name)
{
	printf("----------------------------------------------------------\n");
	printf("| %s : x : %f | y : %f| z : %f    |\n", name, vector.x, vector.y, vector.z);
	printf("----------------------------------------------------------\n");
}
