/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psychedelic_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:42:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 14:47:10 by teliet           ###   ########.fr       */
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
