/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:05:11 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/21 13:47:31 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			result->baby_zombie_count = count;
		else if (!strcmp(type, "NORMAL_ZOMBIE"))
			result->normal_zombie_count = count;
		else if (!strcmp(type, "BIG_ZOMBIE"))
			result->big_zombie_count = count;
		result->total_zombie_count += count;
		zombie = zombie->next;
	}
	result->zombie_killed = 0;
	return (result);
}

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
	result = parse_wave(waves, wave_number);
	cJSON_Delete(root);
	return (result);
}