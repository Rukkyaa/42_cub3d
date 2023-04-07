/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scalar_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:28:41 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 15:11:11 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_scalar_mult(t_vector3d vec1, double i)
{
	t_vector3d	mult;

	mult.x = vec1.x * i;
	mult.y = vec1.y * i;
	mult.z = vec1.z * i;
	return (mult);
}
