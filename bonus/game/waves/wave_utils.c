/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:40:09 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/03 12:01:45 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector3d	get_random_pos(char **map)
{
	t_vector3d	pos;

	while (1)
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
	int	i;

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
	t_wave	*wave;

	wave = game->current_wave;
	if (wave->zombie_killed == wave->total_zombie_count)
	{
		free(game->current_wave);
		game->wave_count++;
		game->current_wave = get_wave(game->wave_count);
		printf("\nReady for wave %d ?\n", game->wave_count);
		spawn_wave(game);
	}
}

void	auto_increase_difficulty(t_wave *wave, int wave_number)
{
	float	coeff;

	coeff = 1 + ((wave_number - 15) / 5);
	wave->baby_zombie_count *= coeff;
	wave->normal_zombie_count *= coeff;
	wave->big_zombie_count *= coeff;
	wave->total_zombie_count *= coeff;
}

void	fill_result(char *type, t_wave *result, int count, cJSON *zombies)
{
	if (!strcmp(type, "BABY_ZOMBIE"))
	{
		result->baby_zombie_count = count;
		result->baby_zombie_stats = get_stats(zombies, type);
	}
	else if (!strcmp(type, "NORMAL_ZOMBIE"))
	{
		result->normal_zombie_count = count;
		result->normal_zombie_stats = get_stats(zombies, type);
	}
	else if (!strcmp(type, "BIG_ZOMBIE"))
	{
		result->big_zombie_count = count;
		result->big_zombie_stats = get_stats(zombies, type);
	}
	result->total_zombie_count += count;
}
