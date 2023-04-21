/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:40:09 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/21 13:54:44 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_wave(t_game *game)
{
	if (game->current_wave->zombie_killed == game->current_wave->total_zombie_count)
	{
		free(game->current_wave);
		game->current_wave = get_wave(game->wave_count + 1);
		game->wave_count++;
		printf("Ready for wave %d ?\n", game->wave_count);
	}
}