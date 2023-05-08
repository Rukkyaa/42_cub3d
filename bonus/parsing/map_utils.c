/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:19:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 17:34:38 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	map_height(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		;
	return (i);
}

int	map_width(char **map)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (map[++i])
	{
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
	}
	return (max);
}

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

char	**map_dup(char **map)
{
	char	**new_map;
	int		i;

	i = -1;
	new_map = malloc(sizeof(char *) * (map_height(map) + 1));
	if (!new_map)
		return (NULL);
	while (map[++i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			free_map(new_map);
			return (NULL);
		}
	}
	new_map[i] = NULL;
	return (new_map);
}
