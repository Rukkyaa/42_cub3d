/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:38:26 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/24 14:35:47 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_grid(t_game *game)
{
	int			i;
	int			j;
	t_vector	pos;

	i = -1;
	while (++i < map_heigth(game->map))
	{
		j = -1;
		while (++j < map_width(game->map))
		{
			pos.x = j * 64;
			pos.y = i * 64;
			if (game->map[i][j] == '1')
				draw_square(game, pos, 64, 0xFFFFFF);
			else
				draw_square(game, pos, 64, 0xFFFFFF);
		}
	}
}

void	clean_map(t_game *game)
{
	int			i;
	int			j;

	i = -1;
	while (++i < map_heigth(game->map))
	{
		j = -1;
		while (++j < map_width(game->map))
		{
			if (game->map[i][j] == 'B')
				game->map[i][j] = '0';
		}
	}
}

void	clear_img(t_img *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < RES_X)
	{
		j = -1;
		while (++j < RES_Y)
		{
			img_pix_put(img, i, j, BLACK_PIXEL);
		}
	}
}

void	load_map(t_game *game)
{
	int			i;
	int			j;
	t_vector	pos;

	i = -1;
	while (++i < map_heigth(game->map))
	{
		j = -1;
		while (++j < (map_width(game->map)))
		{
			pos.x = j * 64;
			pos.y = i * 64;
			if (game->map[i][j] == '1')
				draw_filled_square(game, pos, 64, BLUE_PIXEL);
			else if (game->map[i][j] == '0')
				draw_filled_square(game, pos, 64, GREEN_PIXEL);
			else
				draw_filled_square(game, pos, 64, 888888);
		}
	}
}
