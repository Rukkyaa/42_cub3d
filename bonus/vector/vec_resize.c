/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:37:01 by theo              #+#    #+#             */
/*   Updated: 2023/03/09 13:40:01 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector	vec_resize(t_vector vec1, double i)
{
	t_vector	v_resized;

	v_resized = vec_normalize(vec1);
	v_resized = vec_scalar_mult(v_resized, i);
	return (v_resized);
}
