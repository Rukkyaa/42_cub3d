/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scalar_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:28:41 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/22 11:28:55 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vec_scalar_mult(t_vector vec1, double i)
{
	t_vector	mult;

	mult.x = vec1.x * i;
	mult.y = vec1.y * i;
	return (mult);
}
