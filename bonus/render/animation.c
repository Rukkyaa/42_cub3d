/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:59:39 by theo              #+#    #+#             */
/*   Updated: 2023/04/06 13:09:26 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_animation(t_game *game, t_animation *animation)
{
	int	time_elapsed_ms;
	int	img_index;

	if (animation->nb_imgs == 1)
		return ;
	time_elapsed_ms = (game->time.frame.tv_sec * 1000
			+ game->time.frame.tv_usec / 1000) - animation->start_time_ms;
	img_index = (time_elapsed_ms / animation->frame_duration_ms
			+ animation->frame_offset) % animation->nb_imgs;
	animation->current_img = animation->imgs[img_index];
}
