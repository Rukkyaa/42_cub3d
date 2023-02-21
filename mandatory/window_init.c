/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/21 15:04:07 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	var_init(t_game *game)
{
	int i = 256;
	while(i--)
		game->key_states[i] = 0;
	i = 256;
	while(i--)
		game->key_release_states[i] = 1;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, map_width(game->map) * 64, map_heigth(game->map) * 64, "map");
	game->fps_win = mlx_new_window(game->mlx, RES_X, RES_Y, "first_person");
	game->player.pos.x = 3*64 + 32;
	game->player.pos.y = 3*64 + 32; 
	game->player.direction.x = 1;
	game->player.direction.y = 0; 
	// angle_to_vector( M_PI / 4, &game->player.direction);
    print_vector2D(&game->player.direction, "player dir");
	// close_window(game);
	game->img.mlx_img = mlx_new_image(game->mlx, map_width(game->map) * 64, map_heigth(game->map) * 64);
	game->fps_img.mlx_img = mlx_new_image(game->mlx, RES_X, RES_Y);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->fps_img.addr = mlx_get_data_addr(game->fps_img.mlx_img, &game->fps_img.bpp,
			&game->fps_img.line_len, &game->fps_img.endian);
	load_map(game);
	load_grid(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->fps_win, game->fps_img.mlx_img, 0, 0);
}
