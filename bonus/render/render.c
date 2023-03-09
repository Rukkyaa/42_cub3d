/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:03:13 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 14:03:36 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_map(t_game *game)
{
	render_fps(game);
	if (game->key_states[2])
		psychedelic_view(game, &_mlx()->img);
	load_map(game);
	draw_player(game, RED_PIXEL);

}

void	render(t_game *game)
{
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->win,
		_mlx()->img.mlx_img, 0, 0);
	if (game->key_states['e'])
	{
		put_img_to_img(game->inventory.img, _mlx()->img, 300, 159);
		refresh_inventory(game);
	}
}
