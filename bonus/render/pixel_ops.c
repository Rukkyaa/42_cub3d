/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:36:02 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 14:44:44 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_color(t_img *img, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int *)(img->addr + (4 * (int)img->width * ((int)img->heigth - 1
					- y)) + (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

// ! we replaced (img.bpp / 8) with 4,
//but all image used in the game must be in 32 bitsperpixels
void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * 4);
	*(unsigned int *)dst = color;
}

unsigned int	img_pix_read(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * 4);
	return (*(unsigned int *)pixel);
}

char	*img_get_addr(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * 4);
	return (pixel);
}
