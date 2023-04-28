/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:17:38 by theo              #+#    #+#             */
/*   Updated: 2023/04/28 17:16:02 by teliet           ###   ########.fr       */
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

float	color_interpolate(int color1, int color2, double t)
{
	int	r;
	int	g;
	int	b;

	r = t * (double)(get_r(color2) - get_r(color1)) + get_r(color1);
	g = t * (double)(get_g(color2) - get_g(color1)) + get_g(color1);
	b = t * (double)(get_b(color2) - get_b(color1)) + get_b(color1);
	return (create_trgb(255, r, g, b));
}
