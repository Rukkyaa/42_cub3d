/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/15 17:05:51 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#define MINIAUDIO_IMPLEMENTATION

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	game.map = get_map(argv[1]);
	var_init(&game);
	ma_device_start(&game.sounds.footstep.device);
	hooks(&game);
	mlx_loop(game.mlx);
	ma_device_uninit(&game.sounds.footstep.device);
	clear_sounds(&game.sounds);
	return (EXIT_SUCCESS);
}

