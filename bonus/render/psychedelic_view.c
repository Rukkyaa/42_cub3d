/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psychedelic_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:42:46 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 13:43:00 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	psychedelic_view(t_game *game, t_img *img)
{
	int	i;
	int	j;
	int	pixel_color;
	// printf("%f\n", ((float) (game->time_inc % 300) / 300.0f));
	game->player.direction_adjust = cos(game->time_inc) + 3;
	i = -1;
	while (++i < RES_X)
	{
		j = -1;
		while (++j < RES_Y)
		{
			pixel_color = img_pix_read(img, i, j) + (game->time_inc % 1000) * 500;
			img_pix_put(img, i, j, pixel_color);
		}
	}
}
