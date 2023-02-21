/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:38:26 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/21 13:13:49 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_grid(t_game *game)
{
	int			i;
	int			j;
	t_vector	pos;
	
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
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
	t_vector	pos;
	
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			if (game->map[i][j] == 'B')
				game->map[i][j] = '0';
		}
	}
}

void	clear_img(t_img *img)
{
	int			i;
	int			j;
	
	i = -1;
	while (++i < RES_X)
	{
		j = -1;
		while (++j < RES_Y)
		{
			img_pix_put(img, i , j, BLACK_PIXEL);
		}
	}
}


void	load_map(t_game *game)
{
	int			i;
	int			j;
	t_vector	pos;
	
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
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
