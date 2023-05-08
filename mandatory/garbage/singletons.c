/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:45:53 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 13:59:25 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*_game(void)
{
	static t_game	*game = NULL;

	if (!game)
	{
		game = my_alloc(sizeof(t_game));
		memset(game, 0, sizeof(t_game));
		game->mlx = mlx_init();
		if (!game->mlx)
			free_garbage(MLX_CREATION_ERROR);
		game->fps_win = mlx_new_window(game->mlx,
				RES_X, RES_Y, "first_person");
		game->fps_img.mlx_img = mlx_new_image(game->mlx, RES_X, RES_Y);
		game->fps_img.addr = mlx_get_data_addr(game->fps_img.mlx_img,
				&game->fps_img.bpp, &game->fps_img.line_len,
				&game->fps_img.endian);
		game->fps_img.width = RES_X / 64;
		game->fps_img.heigth = RES_Y / 64;
	}
	return (game);
}

t_garbage	*_gc(void)
{
	static t_garbage	*gc = NULL;

	if (!gc)
	{
		gc = malloc(sizeof(t_garbage));
		if (!gc)
			return (NULL);
		memset(gc, 0, sizeof(t_garbage));
	}
	return (gc);
}
