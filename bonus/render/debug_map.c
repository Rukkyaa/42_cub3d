/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:55:08 by theo              #+#    #+#             */
/*   Updated: 2023/05/01 16:12:52 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_grid(t_game *game)
{
	int			i;
	int			j;
	t_vector3d	pos;

	i = -1;
	while (++i < map_heigth(game->map))
	{
		j = -1;
		while (++j < map_width(game->map))
		{
			pos.x = j * 16;
			pos.y = i * 16;
			if (game->map[i][j] == '1')
				draw_square(&game->debug_img, pos, 16, 0xFFFFFF);
			else
				draw_square(&game->debug_img, pos, 16, 0xFFFFFF);
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
	while (++i < img->width)
	{
		j = -1;
		while (++j < img->heigth)
		{
			img_pix_put(img, i, j, BLACK_PIXEL);
		}
	}
}

void	load_map_debug(t_game *game)
{
	int			i;
	int			j;
	t_vector3d	pos;

	i = -1;
	while (++i < map_heigth(game->map))
	{
		j = -1;
		while (++j < (map_width(game->map)))
		{
			pos.x = MAP_MARGIN + j * 16;
			pos.y = MAP_MARGIN + i * 16;
			if (game->map[i][j] == '1')
				draw_filled_square(&game->debug_img, pos, 16, 0x45475c);
			else if (game->map[i][j] == '0')
				draw_filled_square(&game->debug_img, pos, 16, 0x87888d);
			else
				draw_filled_square(&game->debug_img, pos, 16, 0x45475c);
		}
	}
}
