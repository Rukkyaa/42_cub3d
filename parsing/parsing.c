/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:15:58 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 17:10:10 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	finish_reading(int fd)
{
	char	*line;

	line = "finish";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
	}
	free(line);
}

bool	parse_map(t_parsing *parsing, int fd)
{
	bool		ret;

	ret = true;
	parsing->map = get_map(fd);
	if (!parsing->map)
		ret = false;
	if (ret && !is_map_valid(parsing))
	{
		ret = false;
		free_map(parsing->map);
	}
	if (!ret)
	{
		printf("Map is invalid\n");
		free(parsing);
		return (false);
	}
	return (true);
}

bool	get_params(t_parsing *parsing, int fd)
{
	char	*line;
	int		found;

	found = 0;
	line = "coucou";
	while (line && found < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		if (line[0] == 'F' || line[0] == 'C')
		{
			if (!get_color(parsing, line))
				return (free(line), false);
		}
		if (is_texture(line))
		{
			if (!fill_texture(parsing, line))
				return (free(line), false);
		}
		if (line[0] == 'F' || line[0] == 'C' || is_texture(line))
			found++;
		free(line);
	}
	return (true);
}

t_parsing	*parse(char *map_path)
{
	t_parsing	*parsing;
	int			fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
	{
		close(fd);
		return (NULL);
	}
	memset(parsing, 0, sizeof(t_parsing));
	if (get_params(parsing, fd))
	{
		printf("Floor color: %d %d %d\n", parsing->floor_color[0], parsing->floor_color[1], parsing->floor_color[2]);
		printf("Ceiling color: %d %d %d\n", parsing->ceiling_color[0], parsing->ceiling_color[1], parsing->ceiling_color[2]);
		printf("North texture: %s\n", parsing->no);
		printf("South texture: %s\n", parsing->so);
		printf("West texture: %s\n", parsing->we);
		printf("East texture: %s\n", parsing->ea);
	}
	else
	{
		if (parsing->no)
			free(parsing->no);
		if (parsing->so)
			free(parsing->so);
		if (parsing->we)
			free(parsing->we);
		if (parsing->ea)
			free(parsing->ea);
		printf("Error while parsing params\n");
		finish_reading(fd);
		free(parsing);
		close(fd);
		return (NULL);
	}
	if (!parse_map(parsing, fd))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (parsing);
}
