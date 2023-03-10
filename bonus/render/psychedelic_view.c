/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psychedelic_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:42:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 13:59:35 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	psychedelic_view(t_game *game, t_img *img)
{
	int	i;
	int	j;
	int	pixel_color;
	// printf("%f\n", ((float) (game->frame_count % 300) / 300.0f));
	game->player.direction_adjust = cos(game->frame_count) + 3;
	i = -1;
	while (++i < RES_X)
	{
		j = -1;
		while (++j < RES_Y)
		{
			pixel_color = img_pix_read(img, i, j) + (game->frame_count % 1000) * 500;
			img_pix_put(img, i, j, pixel_color);
		}
	}
}
