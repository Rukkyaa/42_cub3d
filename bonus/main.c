/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/06 11:59:26 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#define MINIAUDIO_IMPLEMENTATION

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (!_gc())
	{
		printf("\033[1;31m[Error]\033[0;31m Creation \
			of the gc's singleton failed\n\033[0m");
		exit(0);
	}
	game = my_alloc(sizeof(t_game));
	if (!game)
		exit(0);
	game->map = get_map(argv[1]);
	var_init(game);
	hooks(game);
	mlx_loop(game->mlx);
	return (EXIT_SUCCESS);
}
