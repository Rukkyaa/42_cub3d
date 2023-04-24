/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:52:25 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 09:46:00 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_sound_playing(ma_sound *sound)
{
	return (ma_sound_is_playing(sound));
}

void	clear_unused_sounds(t_sound_state sound_state,
	ma_sound sounds[NB_SOUNDS])
{
	if (sound_state.player_state == IDLE_STATE)
	{
		if (is_sound_playing(&sounds[WALKING_SOUND]))
			ma_sound_stop(&sounds[WALKING_SOUND]);
		if (is_sound_playing(&sounds[RUNNING_SOUND]))
			ma_sound_stop(&sounds[RUNNING_SOUND]);
	}
	if (sound_state.player_state == WALKING_STATE)
	{
		if (is_sound_playing(&sounds[RUNNING_SOUND]))
			ma_sound_stop(&sounds[RUNNING_SOUND]);
	}
	if (sound_state.player_state == RUNNING_STATE)
	{
		if (is_sound_playing(&sounds[WALKING_SOUND]))
			ma_sound_stop(&sounds[WALKING_SOUND]);
	}
	if (sound_state.game_mode == PLAY)
	{
		if (is_sound_playing(&sounds[LOBBY_SOUND]))
			ma_sound_stop(&sounds[LOBBY_SOUND]);
	}
}

void	play_multiple_sound(ma_sound sounds[NB_SOUNDS], int sound_id,
	int max_sounds)
{
	int	i;

	i = sound_id;
	while (i < sound_id + max_sounds)
	{
		if (!is_sound_playing(&sounds[i]))
		{
			restart_sound(&sounds[i]);
			return ;
		}
		i++;
	}
}

void	game_sound(t_sound_state sound_state, ma_sound sounds[NB_SOUNDS])
{
	clear_unused_sounds(sound_state, sounds);
	if (sound_state.player_state == WALKING_STATE)
		restart_sound(&sounds[WALKING_SOUND]);
	else if (sound_state.player_state == RUNNING_STATE)
		restart_sound(&sounds[RUNNING_SOUND]);
	if (sound_state.player_shooting)
	{
		if (sound_state.player_shooting == AXE)
			play_multiple_sound(sounds, AXE_SOUND, MAX_AXE_SOUNDS);
		else if (sound_state.player_shooting == PLASMA_RIFFLE)
			play_multiple_sound(sounds, PLASMA_RIFFLE_SOUND,
				MAX_PLASMA_RIFFLE_SOUNDS);
		else if (sound_state.player_shooting == GRAP_GUN)
			play_multiple_sound(sounds, PLASMA_SHOOT_SOUND,
				MAX_PLASMA_SHOOT_SOUNDS);
	}
	if (sound_state.player_hurt)
		play_multiple_sound(sounds, PLAYER_HURT_SOUND,
			MAX_PLAYER_HURT_SOUNDS);
	if (sound_state.cocaine)
		restart_sound(&sounds[COCAINE_SOUND]);
	if (sound_state.game_mode == MENU)
		restart_sound(&sounds[LOBBY_SOUND]);
	else
		restart_sound(&sounds[GAME_SOUND]);
}
