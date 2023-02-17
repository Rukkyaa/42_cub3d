/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 13:57:43 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int handle_key_state(void *g)
{
	t_game *game;
	game = (t_game *) g;
	if (game->key_states['w'] || game->key_states['s'] ||game->key_states['a'] ||game->key_states['d'] ||game->key_states[0] ||game->key_states[1])
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
	if (game->key_states[0]) {
		// printf("rotate_left\n");
		rotate(&(game->player.direction), -1);
		// close_window(game);
	}
	if (game->key_states[1] ) {
		// printf("rotate_right\n");
		rotate(&(game->player.direction), 1);
		// close_window(game);
	}
	usleep(16000);
	if (game->key_states['w'] || game->key_states['s'] ||game->key_states['a'] ||game->key_states['d'] ||game->key_states[0] ||game->key_states[1])
		load_grid(game);
	draw_player(game, RED_PIXEL);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
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
