/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_to_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:05:34 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/15 15:28:26 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_img_to_img(t_img *img, t_img *fill, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;

	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->heigth)
		{
			color = img_pix_read(img, x, y);
			if (color != 4278190080)
				img_pix_put(fill, start_x + x, start_y + y, color);
		}
	}
}
