/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:29:25 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:00:44 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector	vec_normalize(t_vector vec)
{
	float		magnitude;
	t_vector	norm_vec;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (magnitude == 0)
		return (vec);
	norm_vec.x = vec.x / magnitude;
	norm_vec.y = vec.y / magnitude;
	return (norm_vec);
}
