/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:17:38 by theo              #+#    #+#             */
/*   Updated: 2023/03/21 11:27:42 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// int	add_shade(int trgb, float shade)
// {
// 	int r, g, b;

// 	r = (float) get_r(trgb) * shade;
// 	g = (float) get_g(trgb) * shade;
// 	b = (float) get_b(trgb) * shade;

// 	return (create_trgb(255, r, g, b));
// }

int add_shade(int trgb, int shade_factor) {
    int r = get_r(trgb);
    int g = get_g(trgb);
    int b = get_b(trgb);
    int r_shaded = ((r * shade_factor) >> 8) & 0xFF;
    int g_shaded = ((g * shade_factor) >> 8) & 0xFF;
    int b_shaded = ((b * shade_factor) >> 8) & 0xFF;
    return create_trgb(255, r_shaded, g_shaded, b_shaded);
}