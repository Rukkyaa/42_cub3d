/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:27:27 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/22 11:27:35 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vec_mult(t_vector vec1, t_vector vec2)
{
	t_vector	mult;

	mult.x = vec1.x * vec2.x;
	mult.y = vec1.y * vec2.y;
	return (mult);
}
