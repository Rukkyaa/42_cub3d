/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:57:52 by teliet            #+#    #+#             */
/*   Updated: 2023/02/27 13:54:58 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	handle_keypress(int keycode, t_game *game)
{
	// printf("%d\n", keycode);
	if (keycode == ESC)
		close_window(game);
	if (keycode == 'w' || keycode == 'a' || keycode == 'd' || keycode == 's'
		|| keycode == 'r' || keycode == 'f')
		{
			ma_device_start(&game->sounds.footstep.device);
			game->key_states[keycode] = 1;
		}
	if (keycode == RIGHT)
		game->key_states[0] = 1;
	if (keycode == LEFT)
		game->key_states[1] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 'a' || keycode == 'd' || keycode == 's'
		|| keycode == 'r' || keycode == 'f')
		game->key_states[keycode] = 0;
	if (keycode == RIGHT)
		game->key_states[0] = 0;
	if (keycode == LEFT)
		game->key_states[1] = 0;
	return (0);
}
