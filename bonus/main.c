/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/24 14:36:49 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	game.map = get_map(argv[1]);
	var_init(&game);
	// mlx_hook(game.win, 2, 1L << 0, key_gestion, &game);
	usleep(1000);
    mlx_hook(game.win, 2, 1L << 1, handle_keypress,  &game);
    mlx_hook(game.win, 3, 1L << 0, handle_keyrelease, &game);
    mlx_hook(game.fps_win, 2, 1L << 1, handle_keypress,  &game);
    mlx_hook(game.fps_win, 3, 1L << 0, handle_keyrelease, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.fps_win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
