/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:14:11 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#define MINIAUDIO_IMPLEMENTATION

int	mouse_hook (int x, int y, void *param )
{
	t_game	*game = (t_game *)param;
	
	int diff_x = x - game->mouse.x;
	if (game->mouse.x > x)
		vec_rotate_edit(&(game->player.direction), diff_x / 50);
	else if (game->mouse.x < x)
		vec_rotate_edit(&(game->player.direction), diff_x / 50);
	game->mouse.x = RES_X / 2;
	mlx_mouse_move(game->mlx, game->fps_win, RES_X / 2, RES_Y / 2);
// int	mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
	// printf("x:%d,y:%d\n", x, y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	game.map = get_map(argv[1]);
	var_init(&game);
	// mlx_hook(game.win, 2, 1L << 0, key_gestion, &game);
	usleep(1000);
	ma_device_start(&game.sounds.footstep.device);
	mlx_mouse_hide(game.mlx, game.fps_win);
    mlx_hook(game.win, 2, 1L << 1, handle_keypress,  &game);
    mlx_hook(game.win, 3, 1L << 0, handle_keyrelease, &game);
    mlx_hook(game.fps_win, 2, 1L << 1, handle_keypress,  &game);
    mlx_hook(game.fps_win, 3, 1L << 0, handle_keyrelease, &game);
	mlx_hook(game.fps_win, 6, 1L << 6, mouse_hook, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.fps_win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	ma_device_uninit(&game.sounds.footstep.device);
	clear_sounds(&game.sounds);
	return (EXIT_SUCCESS);
}
