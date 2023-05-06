/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/06 20:05:54 by rukkyaa          ###   ########.fr       */
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

void	death_animation(t_game *game)
{
	if (game->frame_count - game->player.death_time < 5)
		game->player.pos3d.z -= 3;
	if (game->frame_count - game->player.real_death_time > 100)
		close_window(game);
}

void	update_doors(t_game *game)
{
	t_door	*door;
	int		i;

	i = 0;
	while (game->doors_small[i] != 0)
	{
		door = game->doors_small[i];
		if (door->state == OPENING)
		{
			door->open_state++;
			if (door->open_state == 64)
				door->state = OPEN;
		}
		else if (door->state == CLOSING)
		{
			door->open_state--;
			if (door->open_state == 0)
				door->state = CLOSED;
		}
		i++;
	}
}

void	game_loop(t_game *game)
{
	handle_time(game);
	move_sprites(game, &game->sprites, &game->player);
	if (game->player.hp > 0)
	{
		edit_player_rotate(game);
		edit_player_pos(game);
		inventory_switch(game);
		handle_weapon(game, game->player.weapon);
	}
	else
		death_animation(game);
	update_doors(game);
	render_fps(game);
	render_sprites(game);
	render_ui(game);
	render_map(game);
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
	else if (game->mode == MENU || game->mode == MENU_FADE_OUT)
		render_menu(game);
	if (game->mode == MENU_FADE_OUT)
		menu_fade_out(game);
	if (game->mode == PLAY && game->frame_count - game->game_start_time < 40)
		faded_view(game, &game->fps_img, 255 - (game->frame_count
				- game->game_start_time) * 6);
	render(game);
	if (game->mode == PLAY)
		print_fps(game->time.fps);
	game->player.sound_state.game_mode = game->mode;
	// game_sound(game->player.sound_state, game->audio.sounds);
	handle_sync(game);
	game->frame_count++;
	return (0);
}
