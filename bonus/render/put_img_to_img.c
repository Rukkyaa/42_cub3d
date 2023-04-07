/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_to_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:05:34 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/07 11:41:57 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_img_to_img(t_img *img, t_img *fill, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;
	char	*src_pixel;
	char	*dest_pixel;

	src_pixel = img_get_addr(img, 0, 0);
	dest_pixel = img_get_addr(fill, start_x, start_y);
	y = -1;
	while (++y < img->heigth )
	{
		x = -1;
		while (++x < img->width)
		{
			color = *(unsigned int *)src_pixel;
			//printf("addr %d %d : %p\n", x, y, pixel);
			//color = img_pix_read(img, x, y);
			if (color != 4278190080)
				*(unsigned int *)dest_pixel = color ; //img_pix_put(fill, start_x + x, start_y + y, color); // 
			src_pixel += 4;
			dest_pixel += 4;
		}
		dest_pixel += 4 * (fill->width - img->width);
	}
}

void	put_img_to_img_crop(t_img *img, t_img *fill, t_vector start, t_vector end)
{
	int				x;
	int				y;
	unsigned int	color;
	char	*src_pixel;
	char	*dest_pixel;

	src_pixel = img_get_addr(img, 0, 0);
	dest_pixel = img_get_addr(fill, start.x, start.y);
	y = -1;
	while (++y < (int)(end.y - start.y))
	{
		x = -1;
		while (++x < (int)(end.x - start.x))
		{
			color = *(unsigned int *)src_pixel;
			if (color != 4278190080)
				*(unsigned int *)dest_pixel = color ; //img_pix_put(fill, start_x + x, start_y + y, color); // 
			src_pixel += 4;
			dest_pixel += 4;
		}
		src_pixel += 4 * (img->width - (int)(end.x - start.x));
		dest_pixel += 4 * (fill->width - (int)(end.x - start.x));
	}
}

void	sample_img_to_img(t_img *dest, t_img *src, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;
	char	*src_pixel;
	char	*dest_pixel;

	src_pixel = img_get_addr(src, start_x, start_y);
	dest_pixel = img_get_addr(dest, 0, 0);
	y = -1;
	while (++y < dest->heigth )
	{
		x = -1;
		while (++x < dest->width)
		{
			color = *(unsigned int *)src_pixel;
			//printf("addr %d %d : %p\n", x, y, src_pixel);
			//color = img_pix_read(src, x, y);
			if (color != 4278190080)
				*(unsigned int *)dest_pixel = color ; //img_pix_put(fill, start_x + x, start_y + y, color); // 
			src_pixel += 4 ;
			dest_pixel += 4 ;
		}
		src_pixel += 4 * (src->width - dest->width);
	}
}
