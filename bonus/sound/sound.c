/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:55:43 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:12:52 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	data_callback(ma_device *pDevice, void *pOutput,
	const void *pInput, ma_uint32 frameCount)
{
	ma_decoder	*p_decoder;

	p_decoder = (ma_decoder *)pDevice->pUserData;
	ma_data_source_read_pcm_frames(p_decoder, pOutput, frameCount, NULL);
	(void)pInput;
}

void	load_sound(t_sound *sound, char *name)
{
	ma_decoder_init_file(name, NULL, &sound->decoder);
	ma_data_source_set_looping(&sound->decoder, MA_TRUE);
	sound->device_config = ma_device_config_init(ma_device_type_playback);
	sound->device_config.playback.format = sound->decoder.outputFormat;
	sound->device_config.playback.channels = sound->decoder.outputChannels;
	sound->device_config.sampleRate = sound->decoder.outputSampleRate;
	sound->device_config.dataCallback = data_callback;
	sound->device_config.pUserData = &sound->decoder;
	ma_device_init(NULL, &sound->device_config, &sound->device);
}

void	load_sounds(t_sounds *sounds)
{
	load_sound(&sounds->footstep, "bonus/sound/footstep.mp3");
}

void	clear_sounds(t_sounds *sounds)
{
	ma_decoder_uninit(&sounds->footstep.decoder);
}
