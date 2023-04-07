/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:29:25 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 15:15:53 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_normalize(t_vector3d vec)
{
	float		magnitude;
	t_vector3d	norm_vec;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (magnitude == 0)
		return (vec);
	norm_vec.x = vec.x / magnitude;
	norm_vec.y = vec.y / magnitude;
	norm_vec.z = vec.z / magnitude;
	return (norm_vec);
}
