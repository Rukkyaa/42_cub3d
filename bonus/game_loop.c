/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 14:39:25 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	game_loop(void *g)
{
	t_game	*game;

	game = (t_game *) g;
	handle_time(game);
	render_map(game);
	if (!player_moving(game))
		ma_device_stop(&game->sounds.footstep.device);
	if (is_collectible(game))
	{
		add_item(game, "sword");
		game->map[(int)game->player.pos.y / 64]
			[(int)game->player.pos.x / 64] = '0';
	}
	edit_player_rotate(game);		
	edit_player_pos(game);
	render(game);
	game->time_inc++;
	handle_sync(game);
	mlx_string_put(_mlx()->mlx, _mlx()->win, 100, RES_Y - 20, WHITE_PIXEL, ft_itoa(game->time.fps));
	return (0);
}
