/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:27:27 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/23 16:18:39 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_mult(t_vector3d vec1, t_vector3d vec2)
{
	t_vector3d	mult;

	mult.x = vec1.x * vec2.x;
	mult.y = vec1.y * vec2.y;
	mult.z = vec1.z * vec2.z;
	return (mult);
}
