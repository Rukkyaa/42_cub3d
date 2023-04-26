/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/21 13:56:05 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	clear_z_buffer(t_game *game)
{
	int	i;

	i = 0;
	while (i < RES_X)
	{
		game->z_buffer[i] = 0;
		i++;
	}
}

void	print_fps(int fps)
{
	char	*tmp;

	tmp = ft_itoa(fps);
	mlx_string_put(_mlx()->mlx, _mlx()->win, 100, RES_Y - 20, WHITE_PIXEL, tmp);
	free(tmp);
}

void	game_loop(t_game *game)
{
	handle_time(game);
	edit_player_rotate(game);
	edit_player_pos(game);
	inventory_switch(game);
	handle_weapon(game, game->player.weapon);
	is_colliding(game, game->sprites);
	render_fps(game);
	render_map(game);
	render_sprites(game);
	render_ui(game);
	print_kill(game, game->player.kills, RES_X - 55);
	check_item(game);
	if (!game->inventory_display)
		mlx_mouse_move(game->mlx, game->fps_win, RES_X / 2, RES_Y / 2);
	check_wave(game);
}

int	main_loop(void *g)
{
	t_game	*game;

	game = (t_game *)g;
	game->player.sound_state.player_hurt = false;
	game->player.sound_state.cocaine = false;
	clear_z_buffer(game);
	if (game->mode == PLAY)
		game_loop(game);
	else if (game->mode == MENU)
	{
		render_menu(game);
	}
	render(game);
	if (game->mode == PLAY)
		print_fps(game->time.fps);
	game->player.sound_state.game_mode = game->mode;
	game_sound(game->player.sound_state, game->audio.sounds);
	handle_sync(game);
	game->frame_count++;
	return (0);
}
