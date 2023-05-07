/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:17:59 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 12:45:57 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
** @brief: Add a new malloced line to the map
** @param map: The map to add the line to
** @param line: The line to add to the map
** @return: The new map with the line added
*/
char	**add_line(char **map, char *line)
{
	int		i;
	int		len;
	char	**new_map;

	i = 0;
	while (map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = line;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

/*
** @brief: Parse the map file and return a map
** @param map_path: The path to the map file
** @return: The map
*/
char	**get_map(char *map_path)
{
	char	**map;
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *));
	if (!map)
		return (NULL);
	map[0] = NULL;
	line = get_next_line(fd);
	while (line)
	{
		map = add_line(map, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}
