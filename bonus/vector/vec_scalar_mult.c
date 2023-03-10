/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scalar_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:28:41 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:40 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_scalar_mult(t_vector3d vec1, double i)
{
	t_vector3d	mult;

	mult.x = vec1.x * i;
	mult.y = vec1.y * i;
	return (mult);
}
