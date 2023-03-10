/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:29:25 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:40 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_normalize(t_vector3d vec)
{
	float		magnitude;
	t_vector3d	norm_vec;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (magnitude == 0)
		return (vec);
	norm_vec.x = vec.x / magnitude;
	norm_vec.y = vec.y / magnitude;
	return (norm_vec);
}
