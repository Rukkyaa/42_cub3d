/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 12:58:29 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keycode, t_game *game)
{
	printf("keypressed : %d\n", keycode);
	if (keycode == ESC)
		close_window(game);
	if (keycode == 'w' || keycode == 'a' || keycode == 'd' || keycode == 's' ||  keycode == 'r' ||  keycode == 'f')
		game->key_states[keycode] = 1;
	if (keycode == RIGHT)
		game->key_states[0] = 1;
    if (keycode == LEFT)
		game->key_states[1] = 1;
    if (keycode == SHIFT)
	{
		printf("press\n");
		game->key_states[2] = 1;
	}
	return 0;
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 'a' || keycode == 'd' || keycode == 's' ||  keycode == 'r' ||  keycode == 'f')
		game->key_states[keycode] = 0;
	if (keycode == RIGHT)
		game->key_states[0] = 0;
    if (keycode == LEFT)
		game->key_states[1]= 0;
    if (keycode == SHIFT)
	{
		printf("release\n");
		game->key_states[2] = 0;
	}
	return(0);
}
