/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/09 14:04:18 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_parsing	*parsing;

	_game();
	if (argc != 2)
		return (EXIT_FAILURE);
	parsing = parse(argv[1]);
	if (!parsing)
		return (free_garbage(PARSING_ERROR), EXIT_FAILURE);
	_game()->parsing = parsing;
	var_init();
	usleep(1000);
	mlx_hook(_game()->fps_win, 2, 1L << 1, handle_keypress, _game());
	mlx_hook(_game()->fps_win, 3, 1L << 0, handle_keyrelease, _game());
	mlx_loop_hook(_game()->mlx, game_loop, _game());
	mlx_hook(_game()->fps_win, 17, 0, close_window, _game());
	mlx_loop(_game()->mlx);
	return (EXIT_SUCCESS);
}
