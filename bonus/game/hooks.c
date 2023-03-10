/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:08:15 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 13:49:08 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*get_item(int x, int y, char *items[36])
{
	return (items[(y - 530) / 70 * 12 + (x - 321) / 80]);
}

void	swap_items(int first, int second, char *items[36])
{
	char	*tmp;

	tmp = items[first];
	items[first] = items[second];
	items[second] = tmp;
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1 && game->key_states['e'] && x > 320 && x < 1280 && y > 530
		&& y < 736)
	{
		if (strcmp(get_item(x, y, game->inventory.items), "empty"))
		{
			game->inventory.selected = (y - 530) / 70 * 12 + (x - 321) / 80;
			printf("Selected %d\n", game->inventory.selected);
		}
	}
	// printf("Clicked with button : %d in x:%dy:%d\n", button, x, y);
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	if (button == 1 && game->key_states['e'] && x > 320 && x < 1280 && y > 530
		&& y < 736)
	{
		if (game->inventory.selected != -1)
		{
			printf("Dropped %d\n", game->inventory.selected);
			swap_items((y - 530) / 70 * 12 + (x - 321) / 80,
				game->inventory.selected, game->inventory.items);
		}
	}
	// printf("Release with button : %d in x:%dy:%d\n", button, x, y);
	return (0);
}

int	mouse_mouve_hook(int x, int y, t_game *game)
{
	static int	hide = 0;
	int			diff_x;
	int const	tmp = game->mouse.x;

	(void)y;
	diff_x = x - tmp;
	game->mouse.x = x;
	// printf("%d\n", (int)game->mouse.x);
	if (!game->key_states['e'])
	{
		if (!hide)
		{
			mlx_mouse_hide(game->mlx, _mlx()->win);
			hide = 1;
		}
		rotate_player(game, diff_x / 50);
		game->mouse.x = RES_X / 2;
		mlx_mouse_move(game->mlx, _mlx()->win, RES_X / 2, RES_Y / 2);
	}
	else if (hide)
	{
		mlx_mouse_show(game->mlx, _mlx()->win);
		hide = 0;
	}
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	 printf("%d\n", keycode);
	if (keycode == ESC)
		close_window(game);
	if (is_key(keycode))
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
	mlx_loop_hook(game->mlx, game_loop, game);
}
