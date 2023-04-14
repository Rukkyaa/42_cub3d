/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:52:25 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/14 14:48:03 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_sound_playing(t_game *game, int id)
{
	return (ma_sound_is_playing(&game->audio.sounds[id]));
}

void	clear_unused_sounds(t_game *game)
{
	if (game->player.state == IDLE_STATE)
	{
		if (is_sound_playing(game, WALKING_SOUND))
			ma_sound_stop(&game->audio.sounds[WALKING_SOUND]);
		if (is_sound_playing(game, RUNNING_SOUND))
			ma_sound_stop(&game->audio.sounds[RUNNING_SOUND]);
	}
	if (game->player.state == WALKING_STATE)
	{
		if (is_sound_playing(game, RUNNING_SOUND))
			ma_sound_stop(&game->audio.sounds[RUNNING_SOUND]);
	}
	if (game->player.state == RUNNING_STATE)
	{
		if (is_sound_playing(game, WALKING_SOUND))
			ma_sound_stop(&game->audio.sounds[WALKING_SOUND]);
	}
}

void	game_sound(t_game *game)
{
	clear_unused_sounds(game);
	if (game->player.state == WALKING_STATE)
		restart_sound(&game->audio.sounds[WALKING_SOUND]);
	else if (game->player.state == RUNNING_STATE)
		restart_sound(&game->audio.sounds[RUNNING_SOUND]);
	if (game->player.shooting)
	{
		if (is_sound_playing(game, AXE_SOUND) && game->player.shooting != AXE)
			ma_sound_stop(&game->audio.sounds[AXE_SOUND]);
		if (game->player.shooting == AXE)
			restart_sound(&game->audio.sounds[AXE_SOUND]);
	}
}