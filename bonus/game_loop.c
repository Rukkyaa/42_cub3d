/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/14 23:49:56 by theo             ###   ########.fr       */
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
	clear_img(&game->debug_img);
	handle_time(game);
	// load_map_debug(game);
	// load_grid(game);
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
	render_ui(game);
	render(game);
	render_sprites(game);
	mlx_string_put(game->mlx, game->fps_win, 100 , RES_Y - 20, WHITE_PIXEL, ft_itoa(game->time.fps));
	handle_sync(game);
	game->frame_count++;
	//usleep(16000);
	return (0);
}
