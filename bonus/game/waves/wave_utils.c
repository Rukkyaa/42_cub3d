/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:40:09 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/21 16:08:17 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	get_random_pos(char **map)
{
	t_vector3d	pos;
	while(1)
	{
		pos.x = (double)rand() / (double)RAND_MAX * map_width(map) * 64;
		pos.y = (double)rand() / (double)RAND_MAX * map_heigth(map) * 64;
		pos.z = 0;
		if (map[(int)pos.y / 64][(int)pos.x / 64] == '0')
			return (pos);
	}
}

void	spawn_wave(t_game *game)
{
	int i;

	i = -1;
	while (++i < game->current_wave->baby_zombie_count)
		spawn_zombie(game, get_random_pos(game->map), BABY_ZOMBIE);
	i = -1;
	while (++i < game->current_wave->normal_zombie_count)
		spawn_zombie(game, get_random_pos(game->map), NORMAL_ZOMBIE);
	i = -1;
	while (++i < game->current_wave->big_zombie_count)
		spawn_zombie(game, get_random_pos(game->map), BIG_ZOMBIE);
}

void	check_wave(t_game *game)
{
	if (game->current_wave->zombie_killed == game->current_wave->total_zombie_count)
	{
		free(game->current_wave);
		game->wave_count++;
		if (game->wave_count == 15)
		{
			printf("You win !\n");
			close_window(game);
		}
		game->current_wave = get_wave(game->wave_count);
		printf("\nReady for wave %d ?\n", game->wave_count);
		spawn_wave(game);
	}
}