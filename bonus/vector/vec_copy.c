/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:55:08 by theo              #+#    #+#             */
/*   Updated: 2023/04/07 15:09:59 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	vec_copy(t_vector3d vec1)
{
	t_vector3d	v_copy;

	v_copy.x = vec1.x;
	v_copy.y = vec1.y;
	v_copy.z = vec1.z;
	return (v_copy);
}
