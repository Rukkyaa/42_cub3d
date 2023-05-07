/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:15:58 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 13:00:53 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		return (NULL);
	if (!parse_map(parsing, fd))
		return (NULL);
	
	printf("Map is valid\n");
	close(fd);
	return (parsing);
}
