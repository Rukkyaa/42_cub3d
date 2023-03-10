/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:03:13 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 16:26:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_ui(t_game *game)
{
	if (game->key_states['e'])
	{
		put_img_to_img(game->inventory.img, game->fps_img, 300, 159);
		refresh_inventory(game);
	}
	mlx_string_put(game->mlx, game->fps_win, 100 , RES_Y - 20, WHITE_PIXEL, ft_itoa(game->time.fps));
}

void	render_map(t_game *game)
{
	render_fps(game);
	if (game->key_states[2])
		psychedelic_view(game, &game->fps_img);
	load_map(game);
	load_map_debug(game);
	load_grid(game);
	draw_player(game, RED_PIXEL);
}

void	render(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->debug_win,
		game->debug_img.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->fps_win,
		game->fps_img.mlx_img, 0, 0);
}
