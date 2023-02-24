/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:28:05 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/24 14:36:14 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	vec_distance(t_vector vec1, t_vector vec2)
{
	double	dist;

	dist = sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y)
			* (vec1.y - vec2.y));
	return (dist);
}
