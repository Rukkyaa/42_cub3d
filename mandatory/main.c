/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/17 11:03:32 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	game.map = get_map(argv[1]);
	var_init(&game);
	// mlx_hook(game.win, 2, 1L << 0, key_gestion, &game);
    mlx_hook(game.win, 2, 1L << 1, handle_keypress,  &game);
    mlx_hook(game.win, 3, 1L << 0, handle_keyrelease, &game);
    mlx_loop_hook(game.mlx, handle_key_state, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
