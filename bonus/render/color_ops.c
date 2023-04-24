/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:17:38 by theo              #+#    #+#             */
/*   Updated: 2023/04/24 14:35:01 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	add_shade(int trgb, int shade_factor)
{
	int	r_shaded;
	int	g_shaded;
	int	b_shaded;

	r_shaded = ((get_r(trgb) * shade_factor) >> 8) & 0xFF;
	g_shaded = ((get_g(trgb) * shade_factor) >> 8) & 0xFF;
	b_shaded = ((get_b(trgb) * shade_factor) >> 8) & 0xFF;
	return (create_trgb(255, r_shaded, g_shaded, b_shaded));
}
