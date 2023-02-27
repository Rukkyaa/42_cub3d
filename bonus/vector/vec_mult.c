/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:27:27 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:00:44 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector	vec_mult(t_vector vec1, t_vector vec2)
{
	t_vector	mult;

	mult.x = vec1.x * vec2.x;
	mult.y = vec1.y * vec2.y;
	return (mult);
}
