/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:52:25 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/17 11:23:53 by axlamber         ###   ########.fr       */
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
}

void	play_axe_sound(ma_sound sounds[NB_SOUNDS])
{
	int	i;

	i = AXE_SOUND;
	while (i < AXE_SOUND + MAX_AXE_SOUNDS)
	{
		if (!is_sound_playing(&sounds[i]))
		{
			restart_sound(&sounds[i]);
			return ;
		}
		i++;
	}
}

void	play_plasma_riffle_sound(ma_sound sounds[NB_SOUNDS])
{
	int	i;

	i = PLASMA_RIFFLE_SOUND;
	while (i < PLASMA_RIFFLE_SOUND + MAX_PLASMA_RIFFLE_SOUNDS)
	{
		if (!is_sound_playing(&sounds[i]))
		{
			restart_sound(&sounds[i]);
			return ;
		}
		i++;
	}
}

void	play_plasma_shoot_sound(ma_sound sounds[NB_SOUNDS])
{
	int	i;

	i = PLASMA_SHOOT_SOUND;
	while (i < PLASMA_SHOOT_SOUND + MAX_PLASMA_SHOOT_SOUNDS)
	{
		if (!is_sound_playing(&sounds[i]))
		{
			restart_sound(&sounds[i]);
			return ;
		}
		i++;
	}
}

void	play_player_hurt_sound(ma_sound sounds[NB_SOUNDS])
{
	int	i;

	i = PLAYER_HURT_SOUND;
	while (i < PLAYER_HURT_SOUND + MAX_PLAYER_HURT_SOUNDS)
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
			play_axe_sound(sounds);
		else if (sound_state.player_shooting == PLASMA_RIFFLE)
			play_plasma_riffle_sound(sounds);
		else if (sound_state.player_shooting == GRAP_GUN)
			play_plasma_shoot_sound(sounds);
	}
	if (sound_state.player_hurt)
		play_player_hurt_sound(sounds);
}
