/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:55:43 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 18:12:25 by axlamber         ###   ########.fr       */
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

void	add_sound(t_audio *audio, int id, char *path, float volume)
{
	ma_result	result;

	result = ma_sound_init_from_file(&audio->engine, path,
			0, NULL, NULL, &audio->sounds[id]);
	if (result != MA_SUCCESS)
		return ;
	ma_sound_set_volume(&audio->sounds[id], volume);
}

void	init_sounds(t_audio *audio)
{
	ma_result	result;

	result = ma_engine_init(NULL, &audio->engine);
	if (result != MA_SUCCESS)
		return ;
	load_sounds(audio);
}
