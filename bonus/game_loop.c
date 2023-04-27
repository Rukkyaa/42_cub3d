/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/27 18:31:45 by teliet           ###   ########.fr       */
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

void	death_animation(t_game *game)
{
	edit_player_rotate(game);
	edit_player_pos(game);
	inventory_switch(game);
	handle_weapon(game, game->player.weapon);
}

void	game_loop(t_game *game)
{
	handle_time(game);
	if(game->player.hp > 0)
		death_animation(game);
	else
	{
		if(game->frame_count - game->player.death_time < 5)
			game->player.pos3d.z -= 3;
		if(game->frame_count - game->player.real_death_time > 100)
			close_window(game);
	}
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

void	menu_fade_out(t_game *game)
{
	printf("menu fade out\n");
	faded_view(game, &game->fps_img, (game->frame_count - game->menu_fade_start) * 3);
	if(game->frame_count - game->menu_fade_start > 40)
		game->mode = PLAY;
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
	render(game);
	if (game->mode == PLAY)
		print_fps(game->time.fps);
	game->player.sound_state.game_mode = game->mode;
	game_sound(game->player.sound_state, game->audio.sounds);
	handle_sync(game);
	game->frame_count++;
	return (0);
}
