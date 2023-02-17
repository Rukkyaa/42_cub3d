/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 13:10:52 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_key_state(void *g)
{
	t_game *game;
	game = (t_game *) g;
	int render;

	render = 0;
	
	if (game->key_states['w']) {
		printf("up\n");
		game->player.pos.y -= 3;	
		render = 1;
	}
	if (game->key_states['s'] ) {
		printf("down\n");
		game->player.pos.y += 3;
		render = 1;
	}
	if (game->key_states['a' ]) {
		printf("left\n");
		game->player.pos.x -= 3;
		render = 1;
	}
	if (game->key_states['d'] ) {
		printf("right\n");
		game->player.pos.x += 3;
		render = 1;
	}
	if (game->key_states[0]) {
		// printf("rotate_left\n");
		rotate(&(game->player.direction), -1);
		render = 1;
		// close_window(game);
	}
	if (game->key_states[1] ) {
		// printf("rotate_right\n");
		rotate(&(game->player.direction), 1);
		render = 1;
		// close_window(game);
	}
	// printf("f\n");
	usleep(16600);
	if(render)
	{
		load_map(game);
		load_grid(game);
		draw_player(game, RED_PIXEL);
	}
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
		game->key_states[0] = 1;
    if (keycode == LEFT)
		game->key_states[1] = 1;
	return 0;
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		game->key_states[keycode] = 0;
	if (keycode == RIGHT)
		game->key_states[0] = 0;
    if (keycode == LEFT)
		game->key_states[1]= 0;
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
