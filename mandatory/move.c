/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:23:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/16 17:07:58 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	get_next(t_game *game, char direction)
{
	if (direction == 'N')
		return (game->map[game->player.y / 64 - 1][game->player.x / 64]);
	else if (direction == 'S')
		return (game->map[game->player.y / 64 + 1][game->player.x / 64]);
	else if (direction == 'W')
		return (game->map[game->player.y / 64][game->player.x / 64 - 1]);
	else
		return (game->map[game->player.y / 64][game->player.x / 64 + 1]);
}

void	draw_line(t_game *game, int x, int y, int len, int color)
{
	int	i;

	i = -1;
	while (++i < len)
		mlx_pixel_put(game->mlx, game->win, x + i, y, color);
}

void	draw_square(t_game *game, int x, int y, int width, int color)
{
	int	i;

	i = -1;
	while (++i < width)
		draw_line(game, x, y + i, width, color);
}

void	move(t_game *game, char direction)
{
	char const	next = get_next(game, direction);

	if (next != '1')
	{
		draw_square(game, game->player.x, game->player.y, 64, GREEN_PIXEL);
		if (direction == 'N')
			game->player.y -= 64;
		else if (direction == 'S')
			game->player.y += 64;
		else if (direction == 'W')
			game->player.x -= 64;
		else
			game->player.x += 64;
		draw_square(game, game->player.x, game->player.y, 64, RED_PIXEL);
	}
}
