/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 11:12:29 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#define MINIAUDIO_IMPLEMENTATION

int	mouse_hook(int x, int y, void *param)
{
	static int	hide = 0;
	t_game		*game;
	int			diff_x;

	game = (t_game *)param;
	(void)y;
	diff_x = x - game->mouse.x;
	if (!game->key_states['e'])
	{
		if (!hide)
		{
			mlx_mouse_hide(_mlx()->mlx, _mlx()->win);
			hide = 1;
		}
		if (game->mouse.x > x) 
			vec_rotate_edit(&(game->player.direction), diff_x / 50);
		else if (game->mouse.x < x)
			vec_rotate_edit(&(game->player.direction), diff_x / 50);
		game->mouse.x = RES_X / 2;
		mlx_mouse_move(_mlx()->mlx, _mlx()->win, RES_X / 2, RES_Y / 2);
	}
	else if (hide)
	{
		mlx_mouse_show(_mlx()->mlx, _mlx()->win);
		hide = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	game.map = get_map(argv[1]);
	var_init(&game);
	usleep(1000);
	ma_device_start(&game.sounds.footstep.device);
	mlx_hook(_mlx()->win, 2, 1L << 1, handle_keypress, &game);
	mlx_hook(_mlx()->win, 3, 1L << 0, handle_keyrelease, &game);
	mlx_hook(_mlx()->win, 6, 1L << 6, mouse_hook, &game);
	mlx_hook(_mlx()->win, 17, 0, close_window, &game);
	mlx_loop_hook(_mlx()->mlx, game_loop, &game);
	mlx_loop(_mlx()->mlx);
	ma_device_uninit(&game.sounds.footstep.device);
	clear_sounds(&game.sounds);
	return (EXIT_SUCCESS);
}

