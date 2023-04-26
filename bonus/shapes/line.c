/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/26 14:47:31 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_vertical_line_2(t_img *img, t_vector3d pos, int len, int color)
{
	int	i;

	i = -1;
	while (++i < pos.y)
		img_pix_put(img, pos.x, i, 0x191970);
	i = -1;
	while (++i < len)
	{
		img_pix_put(img, pos.x, pos.y + i, color);
	}
	while (i < RES_Y)
		img_pix_put(img, pos.x, pos.y + i++, 0x87CEEB);
}

void	draw_vertical_line(t_img *img, t_vector3d pos, int len, int color)
{
	int	i;

	i = -1;
	while (++i < len)
		img_pix_put(img, pos.x + i, pos.y, color);
}

void	draw_line_dda(t_img *img, t_vector3d vec1, t_vector3d vec2, int color)
{
	int		steps;
	int		i;
	float	x_inc;
	float	y_inc;

	if (abs((int)(vec2.x - vec1.x)) > abs((int)(vec2.y - vec1.y)))
		steps = abs((int)(vec2.x - vec1.x));
	else
		steps = abs((int)(vec2.y - vec1.y));
	x_inc = (int)(vec2.x - vec1.x) / (float)steps;
	y_inc = (int)(vec2.y - vec1.y) / (float)steps;
	i = 0;
	while (i <= steps)
	{
		img_pix_put(img, round(vec1.x), round(vec1.y), color);
		vec1.x += x_inc;
		vec1.y += y_inc;
		i++;
	}
}
