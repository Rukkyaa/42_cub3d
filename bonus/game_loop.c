/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/05 10:46:33 by axlamber         ###   ########.fr       */
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

void	print_fps(int fps)
{
	char	*tmp;

	tmp = ft_itoa(fps);
	mlx_string_put(_mlx()->mlx, _mlx()->win, 100 , RES_Y - 20, WHITE_PIXEL, tmp);
	free(tmp);
}

int	game_loop(void *g)
{
	t_game	*game;

	game = (t_game *) g;
	clear_z_buffer(game);
	handle_time(game);
	// load_map_debug(game);
	// load_grid(game);
	// if (!player_moving(game))
	// 	ma_device_stop(&game->sounds.footstep.device);
	edit_player_rotate(game);		
	edit_player_pos(game);
	is_colliding(game, game->sprites);
	render_map(game);
	if(game->mouse_clicked)
		spawn_projectile(game, game->player.pos);
	render_sprites(game);
	render_ui(game);
	render(game);
	print_fps(game->time.fps);
	handle_sync(game);
	print_kill(game, game->player.kills, RES_X - 55);
	game->frame_count++;
	//usleep(16000);
	return (0);
}
