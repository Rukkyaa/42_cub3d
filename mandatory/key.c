/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 11:18:19 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_key_state(void *g)
{
	t_game *game;
	game = (t_game *) g;
	draw_player(game, GREEN_PIXEL);
	if (game->key_states['w']) {
		printf("up\n");
		game->player.pos.y -= 3;
	}
	if (game->key_states['s'] ) {
		printf("down\n");
		game->player.pos.y += 3;
	}
	if (game->key_states['a' ]) {
		printf("left\n");
		game->player.pos.x -= 3;
	}
	if (game->key_states['d'] ) {
		printf("right\n");
		game->player.pos.x += 3;
	}
	usleep(16000);
	draw_player(game, RED_PIXEL);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	printf("%d\n", keycode);
	if (keycode == ESC)
		close_window(game);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		game->key_states[keycode] = 1;
	if (keycode == RIGHT)
		game->key_states[0];
    if (keycode == LEFT)
		game->key_states[1];
	return 0;
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		game->key_states[keycode] = 0;
	if (keycode == RIGHT)
		game->key_states[0];
    if (keycode == LEFT)
		game->key_states[1];
	return(0);
}

// int	key_gestion(int keycode, t_game *game)
// {
// 	if (keycode == ESC)
// 		close_window(game);
// 	else if (keycode == W)
// 		move(game, 'N');
// 	else if (keycode == S)
// 		move(game, 'S');
// 	else if (keycode == A)
// 		move(game, 'W');
// 	else if (keycode == D)
// 		move(game, 'E');
// 	return (0);
// }
