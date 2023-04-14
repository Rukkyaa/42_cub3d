/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:55:43 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/14 14:49:52 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	play_sound(ma_sound *sound)
{
	if (!ma_sound_is_playing(sound))
		ma_sound_start(sound);
}

void	restart_sound(ma_sound *sound)
{
	if (!ma_sound_is_playing(sound))
	{
		ma_sound_set_start_time_in_pcm_frames(sound, 0);
		ma_sound_start(sound);
	}
}

void	add_sound(t_audio *audio, int id, char *path)
{
	ma_result	result;

	result = ma_sound_init_from_file(&audio->engine, path, 0, NULL, NULL, &audio->sounds[id]);
	if (result != MA_SUCCESS)
	{
		printf("Failed to load sound: %s\n", ma_result_description(result));
		// EXIT GAME
	}
	ma_sound_set_volume(&audio->sounds[id], 0.5f);
}

void	load_sounds(t_audio *audio)
{
	add_sound(audio, RUNNING_SOUND, "bonus/sound/dejavu.mp3");
	add_sound(audio, WALKING_SOUND, "bonus/sound/footstep.mp3");
	add_sound(audio, AXE_SOUND, "bonus/sound/axe.mp3");
}

void	init_sounds(t_audio *audio)
{
	ma_result	result;

	result = ma_engine_init(NULL, &audio->engine);
	if (result != MA_SUCCESS)
	{
		printf("Failed to initialize audio engine: %s\n", ma_result_description(result));
		// EXIT GAME
	}
	load_sounds(audio);
}