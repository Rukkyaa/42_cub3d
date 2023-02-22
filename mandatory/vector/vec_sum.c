/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:25:33 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/22 11:27:20 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vec_sum(t_vector vec1, t_vector vec2)
{
	t_vector	sum;

	sum.x = vec1.x + vec2.x;
	sum.y = vec1.y + vec2.y;
	return (sum);
}
