/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:35:58 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 13:38:30 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	time_elapsed_ms(struct timeval start_time, struct timeval now)
{
	return ((now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec
			- start_time.tv_usec) / 1000);
}

void	handle_sync(t_game *game)
{
	struct timeval frame_end;
	long frame_duration;
	
	gettimeofday(&frame_end, NULL);
	frame_duration = time_elapsed_ms(game->time.frame, frame_end);
	if(frame_duration < 17)
		usleep((17 - frame_duration) * 1000);
}

void	handle_time(t_game *game)
{
	static int	first_call = 1;
	
	game->time.last_frame.tv_sec = game->time.frame.tv_sec;
	game->time.last_frame.tv_usec = game->time.frame.tv_usec;
	gettimeofday(&game->time.frame, NULL);
	if (first_call)
	{
		first_call = 0;
		game->time.fps = 0;
		return ;
	}
	game->time.delta_frame_ms = time_elapsed_ms(game->time.last_frame, game->time.frame);
	game->time.fps = 1000.0f / (float) game->time.delta_frame_ms;
}
