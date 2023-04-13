/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/14 00:34:29 by theo             ###   ########.fr       */
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
	if(game->mode == PLAY)
	{
		edit_player_rotate(game);		
		edit_player_pos(game);		
		inventory_switch(game);
		handle_weapon(game, game->player.weapon);
		is_colliding(game, game->sprites);
		render_map(game);
		render_fps(game);
		render_sprites(game);
		handle_sync(game);
		print_kill(game, game->player.kills, RES_X - 55);
		check_item(game);
		if (!game->inventory_display)
			mlx_mouse_move(game->mlx, game->fps_win, RES_X / 2, RES_Y / 2);
		render_ui(game);
		print_fps(game->time.fps);
	}
	if(game->mode == MENU)
	{
		render_menu(game);
	}
	render(game);
	game->frame_count++;
	//usleep(16000);
	return (0);
}
