/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:36:02 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/24 14:35:41 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_color(t_img *img, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int *)(img->addr
			+ (4 * (int)img->width * ((int)img->heigth - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

unsigned int img_pix_read(t_img *img, int x, int y)
{
	char *pixel;

	if(pixel_out_of_bound(x, y, img))
		return (0);
    pixel = ( img->addr + (y * img->line_len + x * (img->bpp / 8)));
	return(*(unsigned int *)pixel);
}
