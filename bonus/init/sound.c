/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:20:47 by theo              #+#    #+#             */
/*   Updated: 2023/04/26 12:21:06 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sound_state_init(t_sound_state *sound_state)
{
	sound_state->player_state = IDLE;
	sound_state->player_shooting = 0;
	sound_state->player_hurt = false;
	sound_state->cocaine = false;
	sound_state->game_mode = MENU;
}
