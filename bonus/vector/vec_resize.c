/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:37:01 by theo              #+#    #+#             */
/*   Updated: 2023/04/07 15:10:08 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_resize(t_vector3d vec1, double i)
{
	t_vector3d	v_resized;

	v_resized = vec_normalize(vec1);
	v_resized = vec_scalar_mult(v_resized, i);
	return (v_resized);
}
