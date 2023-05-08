/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:07:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 17:49:32 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#define MINIAUDIO_IMPLEMENTATION

int	main(int argc, char **argv)
{
	t_parsing	*parsing;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (!_gc())
	{
		printf("\033[1;31m[Error]\033[0;31m Creation \
			of the gc's singleton failed\n\033[0m");
		exit(0);
	}
	parsing = parse(argv[1]);
	if (!parsing)
		return (EXIT_FAILURE);
	_game()->parsing = parsing;
	var_init(_game());
	hooks(_game());
	mlx_loop(_mlx()->mlx);
	return (EXIT_SUCCESS);
}
