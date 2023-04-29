/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:08:15 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/29 16:17:17 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1 && game->inventory_display && x > 320 && x < 1280 && y > 530
		&& y < 736)
	{
		if (get_item(x, y, game->inventory.items) != 0)
		{
			game->inventory.selected = (y - 530) / 70 * 12 + (x - 321) / 80;
			select_item(game, x, y);
		}
	}
	if (!game->inventory_display)
		game->mouse_clicked = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	if (!game->inventory_display)
		game->mouse_clicked = 0;
	if (button == 1 && game->inventory_display && x > 320 && x < 1280 && y > 530
		&& y < 736)
		if (game->inventory.selected != -1)
			swap_items((y - 530) / 70 * 12 + (x - 321) / 80,
				game->inventory.selected,
				game->inventory.items);
	game->inventory.selected = -1;
	return (0);
}

int	mouse_mouve_hook(int x, int y, t_game *game)
{
	int	diff_x;
	int	diff_y;

	diff_x = x - RES_X / 2;
	diff_y = y - RES_Y / 2;
	if (!game->inventory_display)
	{
		if ((diff_x != 0 || diff_y != 0))
		{
			game->mouse_move = 1;
			game->mouse_diff.x = diff_x;
			game->mouse_diff.y = diff_y;
			game->mouse.x = x;
			game->mouse.y = y;
		}
	}
	else
	{
		game->mouse_move = 1;
		game->mouse.x = x;
		game->mouse.y = y;
	}
	return (0);
}
