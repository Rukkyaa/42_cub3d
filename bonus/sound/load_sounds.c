/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:09:53 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 18:12:32 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_weapon_sounds(t_audio *audio)
{
	int	i;

	i = AXE_SOUND;
	while (i < AXE_SOUND + MAX_AXE_SOUNDS)
	{
		add_sound(audio, i, "bonus/sound/axe.mp3", 1);
		i++;
	}
}

void	load_plasma_riffle_sounds(t_audio *audio)
{
	int	i;

	i = PLASMA_RIFFLE_SOUND;
	while (i < PLASMA_RIFFLE_SOUND + MAX_PLASMA_RIFFLE_SOUNDS)
	{
		add_sound(audio, i, "bonus/sound/plasma_riffle.wav", 1);
		i++;
	}
}

void	load_plasma_sounds(t_audio *audio)
{
	int	i;

	i = PLASMA_SHOOT_SOUND;
	while (i < PLASMA_SHOOT_SOUND + MAX_PLASMA_SHOOT_SOUNDS)
	{
		add_sound(audio, i, "bonus/sound/plasma_shoot.wav", 1);
		i++;
	}
}

void	load_player_hurt_sounds(t_audio *audio)
{
	int	i;

	i = PLAYER_HURT_SOUND;
	while (i < PLAYER_HURT_SOUND + MAX_PLAYER_HURT_SOUNDS)
	{
		add_sound(audio, i, "bonus/sound/hurt.wav", 1);
		i++;
	}
}

void	load_sounds(t_audio *audio)
{
	add_sound(audio, RUNNING_SOUND, "bonus/sound/dejavu.mp3", 1);
	add_sound(audio, WALKING_SOUND, "bonus/sound/footstep.mp3", 1);
	add_sound(audio, COCAINE_SOUND, "bonus/sound/snif_pjay.wav", 1);
	add_sound(audio, LOBBY_SOUND, "bonus/sound/lobby_sound.wav", 0.8f);
	add_sound(audio, GAME_SOUND, "bonus/sound/game_sound.wav", 0.8f);
	load_weapon_sounds(audio);
	load_plasma_riffle_sounds(audio);
	load_plasma_sounds(audio);
	load_player_hurt_sounds(audio);
}
