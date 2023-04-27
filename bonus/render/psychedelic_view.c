/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psychedelic_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:42:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/27 16:14:35 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	psychedelic_view(t_game *game, t_img *img)
{
	int	i;
	int	j;
	int	pixel_color;

	game->player.direction_adjust = cos(game->frame_count) + 3;
	i = -1;
	while (++i < RES_X)
	{
		j = -1;
		while (++j < RES_Y)
		{
			pixel_color = img_pix_read(img, i, j) + (game->frame_count % 1000)
				* 500;
			img_pix_put(img, i, j, pixel_color);
		}
	}
}

void	red_view(t_game *game, t_img *img)
{
	int	i;
	int	j;
	char *src_pixel;
	int	pixel_color;
	float	lerp;

	src_pixel = img_get_addr(img, 0, 0);
	lerp = ((float) (game->frame_count - game->player.real_death_time)) / 120.0f;
	if(lerp > 1)
		lerp = 1;	
	// printf(" game->player.real_death_time = %d\n",  game->player.real_death_time);
	// printf("game->frame_count  = %d\n", game->frame_count );
	// printf("lerp = %f\n", lerp);
	game->player.direction_adjust = cos(game->frame_count) + 3;
	i = -1;
	while (++i < RES_X)
	{
		j = -1;
		while (++j < RES_Y)
		{
			*(unsigned int *)src_pixel = color_interpolate(*(unsigned int *)src_pixel, RED_PIXEL, lerp);
			src_pixel += 4;
		}
	}
}
