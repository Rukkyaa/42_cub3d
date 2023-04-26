/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_windows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/26 12:26:26 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_windows(t_game *game)
{
	game->debug_img.mlx_img = mlx_new_image(game->mlx, map_width(game->map) * 16
			+ MAP_MARGIN * 2, map_heigth(game->map) * 16 + MAP_MARGIN * 2);
	game->debug_img.addr = mlx_get_data_addr(game->debug_img.mlx_img,
			&game->debug_img.bpp, &game->debug_img.line_len,
			&game->debug_img.endian);
	game->minimap.mlx_img = mlx_new_image(game->mlx, 224, 224);
	game->minimap.addr = mlx_get_data_addr(game->minimap.mlx_img,
			&game->minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
	game->minimap.width = 224;
    game->minimap.heigth = 224;
	game->minimap_center.x = game->minimap.width / 2;
	game->minimap_center.y = game->minimap.heigth / 2;
	game->debug_img.width = map_width(game->map) * 16 + MAP_MARGIN * 2;
	game->debug_img.heigth = map_heigth(game->map) * 16 + MAP_MARGIN * 2;
	game->fps_win = _mlx()->win;
	game->fps_img = _mlx()->img;
}
