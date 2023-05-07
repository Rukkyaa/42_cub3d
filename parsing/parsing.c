/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:15:58 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 13:31:58 by rukkyaa          ###   ########.fr       */
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
	if (get_params(parsing, fd))
	{
		printf("Floor color: %d %d %d\n", parsing->floor_color[0], parsing->floor_color[1], parsing->floor_color[2]);
		printf("Ceiling color: %d %d %d\n", parsing->ceiling_color[0], parsing->ceiling_color[1], parsing->ceiling_color[2]);
	}
	else
	{
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
