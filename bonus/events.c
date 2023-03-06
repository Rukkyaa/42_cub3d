/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:57:52 by teliet            #+#    #+#             */
/*   Updated: 2023/03/06 13:35:07 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	handle_keypress(int keycode, t_game *game)
{
	// printf("%d\n", keycode);
	if (keycode == ESC)
		close_window(game);
	if (keycode == 'w' || keycode == 'a' || keycode == 'd' || keycode == 's'
		|| keycode == 'r' || keycode == 'f')
		game->key_states[keycode] = 1;
	if (keycode == 'e' && game->key_states[keycode] == 0)
		game->key_states[keycode] = 1;
	else if (keycode == 'e' && game->key_states[keycode] == 1)
		game->key_states[keycode] = 0;
	if (keycode == RIGHT)
		game->key_states[0] = 1;
	if (keycode == LEFT)
		game->key_states[1] = 1;
    if (keycode == SHIFT)
		game->key_states[2] = 1;
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
    if (keycode == SHIFT)
		game->key_states[2] = 0;
	return (0);
}
