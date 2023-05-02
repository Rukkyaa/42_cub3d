/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:08:15 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/02 15:04:57 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_alpha(int keycode)
{
	return ((('a' <= keycode && keycode <= 'z') && keycode != 'e')
		|| ('0' <= keycode && keycode <= '9'));
}

void	handle_inventory(t_game *game)
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

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (is_alpha(keycode))
		game->key_states[keycode] = 1;
	if (keycode == 'e')
		handle_inventory(game);
	if (keycode == RIGHT)
		game->key_states[0] = 1;
	if (keycode == LEFT)
		game->key_states[1] = 1;
	if (keycode == SHIFT)
		game->key_states[2] = 1;
	if (keycode == 32)
		game->key_states[32] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, int *key_states)
{
	if (is_alpha(keycode))
		key_states[keycode] = 0;
	if (keycode == RIGHT)
		key_states[0] = 0;
	if (keycode == LEFT)
		key_states[1] = 0;
	if (keycode == SHIFT)
		key_states[2] = 0;
	if (keycode == 32)
		key_states[32] = 0;
	return (0);
}
