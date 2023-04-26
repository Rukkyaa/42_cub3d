/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:08:15 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 18:18:51 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	swap_items(int first, int second, int items[36])
{
	int	tmp;

	tmp = items[first];
	items[first] = items[second];
	items[second] = tmp;
}

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
				game->inventory.selected, game->inventory.items);
	game->inventory.selected = -1;
	return (0);
}

int	mouse_mouve_hook(int x, int y, t_game *game)
{
	int			diff_x;
	int			diff_y;

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

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (is_key(keycode))
		game->key_states[keycode] = 1;
	if (keycode == 'e')
	{
		if (game->inventory_display)
		{
			game->inventory_display = 0;
			mlx_mouse_hide(game->mlx, _mlx()->win);
		}
		else
		{
			game->inventory_display = 1;
			mlx_mouse_show(game->mlx, _mlx()->win);
		}
	}
	if (keycode == RIGHT)
		game->key_states[0] = 1;
	if (keycode == LEFT)
		game->key_states[1] = 1;
	if (keycode == SHIFT)
		game->key_states[2] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, int *key_states)
{
	if (is_key(keycode))
		key_states[keycode] = 0;
	if (keycode == RIGHT)
		key_states[0] = 0;
	if (keycode == LEFT)
		key_states[1] = 0;
	if (keycode == SHIFT)
		key_states[2] = 0;
	return (0);
}

void	hooks(t_game *game)
{
	mlx_hook(_mlx()->win, 2, 1L << 1, handle_keypress, game);
	mlx_hook(_mlx()->win, 3, 1L << 0, handle_keyrelease, game->key_states);
	mlx_hook(_mlx()->win, 6, 1L << 6, mouse_mouve_hook, game);
	mlx_hook(_mlx()->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(_mlx()->win, 5, 1L << 3, mouse_release, game);
	mlx_hook(_mlx()->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, main_loop, game);
}
