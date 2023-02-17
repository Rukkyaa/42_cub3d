/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:38:26 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 14:39:19 by axlamber         ###   ########.fr       */
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
			else
				draw_filled_square(game, pos, 64, GREEN_PIXEL);
		}
	}
}
