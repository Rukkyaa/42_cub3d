/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:52:25 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/17 10:23:50 by axlamber         ###   ########.fr       */
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

void	play_axe_sound(t_game *game)
{
	int	i;

	i = AXE_SOUND;
	while (i < AXE_SOUND + MAX_AXE_SOUNDS)
	{
		if (!is_sound_playing(game, i))
		{
			restart_sound(&game->audio.sounds[i]);
			return ;
		}
		i++;
	}
}

void	play_plasma_riffle_sound(t_game *game)
{
	int	i;

	i = PLASMA_RIFFLE_SOUND;
	while (i < PLASMA_RIFFLE_SOUND + MAX_PLASMA_RIFFLE_SOUNDS)
	{
		if (!is_sound_playing(game, i))
		{
			restart_sound(&game->audio.sounds[i]);
			return ;
		}
		i++;
	}
}

void	play_plasma_shoot_sound(t_game *game)
{
	int	i;

	i = PLASMA_SHOOT_SOUND;
	while (i < PLASMA_SHOOT_SOUND + MAX_PLASMA_SHOOT_SOUNDS)
	{
		if (!is_sound_playing(game, i))
		{
			restart_sound(&game->audio.sounds[i]);
			return ;
		}
		i++;
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
		if (game->player.shooting == AXE)
			play_axe_sound(game);
		else if (game->player.shooting == PLASMA_RIFFLE)
			play_plasma_riffle_sound(game);
		else if (game->player.shooting == GRAP_GUN)
			play_plasma_shoot_sound(game);
	}
}