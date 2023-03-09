/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 18:12:11 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	clear_z_buffer(t_game *game)
{
	int i = 0;
	while(i < RES_X)
	{
		game->z_buffer[i] = 0;
		i++;
	}
}

int	game_loop(void *g)
{
	t_game	*game;

	game = (t_game *) g;
	clear_z_buffer(game);
	handle_time(game);
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
	render_map(game);
	render(game);
	game->time_inc++;
	handle_sync(game);
	render_sprites(game);
	render_ui(game);
	//usleep(16000);
	return (0);
}
