/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:15:58 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/09 14:05:17 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	parsing->map = get_map_parse(fd);
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
			if (!get_map_color(parsing, line))
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

void	free_texture(t_parsing *parsing)
{
	if (parsing->no)
		free(parsing->no);
	if (parsing->so)
		free(parsing->so);
	if (parsing->we)
		free(parsing->we);
	if (parsing->ea)
		free(parsing->ea);
}

t_parsing	*parse(char *map_path)
{
	t_parsing	*parsing;
	int			fd;

	if (!is_valid_map_name(map_path))
		return (NULL);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (close(fd), NULL);
	memset(parsing, 0, sizeof(t_parsing));
	if (!get_params(parsing, fd))
	{
		free_texture(parsing);
		finish_reading(fd);
		free(parsing);
		close(fd);
		return (NULL);
	}
	if (!parse_map(parsing, fd))
		return (free_texture(parsing), free(parsing), close(fd), NULL);
	close(fd);
	return (parsing);
}
