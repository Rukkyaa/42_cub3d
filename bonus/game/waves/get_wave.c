/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:05:11 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/29 16:30:32 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

cJSON	*get_root(const char *filename)
{
	FILE	*file;
	cJSON	*root;
	long	file_size;
	char	*file_contents;

	file = fopen(filename, "rb");
	if (!file)
		return (NULL);
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	file_contents = malloc(file_size + 1);
	if (fread(file_contents, file_size, 1, file) != 1)
	{
		fclose(file);
		free(file_contents);
		return (NULL);
	}
	fclose(file);
	file_contents[file_size] = '\0';
	root = cJSON_Parse(file_contents);
	free(file_contents);
	return (root);
}

t_stats	get_stats(cJSON *zombies, const char *type)
{
	cJSON	*zombie;
	cJSON	*stats_json;
	t_stats	stats;

	stats = (t_stats){0, 0, 0, 0};
	zombie = cJSON_GetArrayItem(zombies, 0);
	while (zombie)
	{
		if (!strcmp(cJSON_GetObjectItem(zombie, "type")->valuestring, type))
		{
			stats_json = cJSON_GetObjectItem(zombie, "stats");
			stats.velocity = cJSON_GetObjectItem(stats_json,
					"velocity")
				->valuedouble;
			stats.hp = cJSON_GetObjectItem(stats_json, "health")->valueint;
			stats.damage = cJSON_GetObjectItem(stats_json, "damage")->valueint;
			stats.range = cJSON_GetObjectItem(stats_json, "range")->valueint;
			break ;
		}
		zombie = zombie->next;
	}
	return (stats);
}

t_wave	*count_zombie_types(cJSON *zombies)
{
	t_wave	*result;
	cJSON	*zombie;
	char	*type;
	int		count;

	result = calloc(1, sizeof(t_wave));
	zombie = cJSON_GetArrayItem(zombies, 0);
	while (zombie)
	{
		type = cJSON_GetObjectItem(zombie, "type")->valuestring;
		count = cJSON_GetObjectItem(zombie, "count")->valueint;
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
		zombie = zombie->next;
	}
	result->zombie_killed = 0;
	return (result);
}

t_wave	*parse_wave(cJSON *waves, int wave_number)
{
	cJSON	*wave;
	cJSON	*zombies;
	t_wave	*result;
	int		number;

	wave = cJSON_GetArrayItem(waves, 0);
	while (wave)
	{
		number = cJSON_GetObjectItem(wave, "number")->valueint;
		if (number == wave_number)
		{
			zombies = cJSON_GetObjectItem(wave, "zombies");
			if (!zombies)
				return (NULL);
			result = count_zombie_types(zombies);
			return (result);
		}
		wave = wave->next;
	}
	return (NULL);
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

t_wave	*get_wave(int wave_number)
{
	cJSON	*root;
	cJSON	*waves;
	t_wave	*result;

	root = get_root(WAVE_FILE);
	if (!root)
		return (NULL);
	waves = cJSON_GetObjectItem(root, "waves");
	if (!waves)
	{
		cJSON_Delete(root);
		return (NULL);
	}
	if (wave_number > 15)
	{
		result = parse_wave(waves, 15);
		auto_increase_difficulty(result, wave_number);
	}
	else
		result = parse_wave(waves, wave_number);
	cJSON_Delete(root);
	return (result);
}
