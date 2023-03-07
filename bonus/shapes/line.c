/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/07 14:44:51 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


// unsigned int img_pix_read(t_img *img, int x, int y)
// {
// 	char *pixel;

// 	if(pixel_out_of_bound(x, y, img))
// 		return (0);
//     pixel = ( img->addr + (y * img->line_len + x * (img->bpp / 8)));
// 	return(*(unsigned int *)pixel);
// }

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }



// void	img_pix_put(t_img *img, int x, int y, int color)
// {
// 	char	*pixel;
// 	int		i;

// 	// if (pixel_out_of_bound(x, y, img))
// 	// 	return ;
// 	i = img->bpp - 8;
// 	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	while (i >= 0)
// 	{
// 		if (img->endian != 0)
// 			*pixel++ = (color >> i) & 0xFF;
// 		else
// 			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
// 		i -= 8;
// 	}
// }

void	draw_vertical_line_2(t_img *img, t_vector pos, int len, int color)
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

void	draw_vertical_line(t_img *img, t_vector pos, int len, int color)
{
	int	i;

	i = -1;
	while (++i < len)
		img_pix_put(img, pos.x + i, pos.y, color);
}

void	draw_line_dda(t_img *img, t_vector vec1, t_vector vec2, int color)
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

void	draw_line(t_game *game, t_vector posA, t_vector posB, int thickness,
		int color)
{
	float	dx;
	float	dy;
	int		x_dir;
	int		y_dir;
	float	error;
	float	delta_x;
	float	delta_y;
	int		x;
	int		y;
	float	error2;

	dx = posB.x - posA.x;
	dy = posB.y - posA.y;
	x_dir = dx > 0 ? 1 : -1;
	y_dir = dy > 0 ? 1 : -1;
	dx = fabsf(dx);
	dy = fabsf(dy);
	error = dx - dy;
	delta_x = x_dir;
	delta_y = y_dir;
	x = (int)posA.x;
	y = (int)posA.y;
	while (x != (int)posB.x || y != (int)posB.y)
	{
		for (int i = 0; i < thickness; i++)
		{
			for (int j = 0; j < thickness; j++)
			{
				img_pix_put(&game->img, x + i, y + j, color);
			}
		}
		error2 = 2 * error;
		if (error2 > -dy)
		{
			error -= dy;
			x += delta_x;
		}
		if (error2 < dx)
		{
			error += dx;
			y += delta_y;
		}
	}
	for (int i = 0; i < thickness; i++)
	{
		for (int j = 0; j < thickness; j++)
		{
			img_pix_put(&game->img, x + i, y + j, color);
		}
	}
}
