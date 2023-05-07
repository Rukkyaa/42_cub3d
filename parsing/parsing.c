/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:15:58 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 12:56:10 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_map(t_parsing *parsing, char *map_path)
{
	bool		ret;

	ret = true;
	parsing->map = get_map(map_path);
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

t_parsing	*parse(char	*map_path)
{
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (NULL);
	if (!parse_map(parsing, map_path))
		return (NULL);
	printf("Map is valid\n");
	return (parsing);
}
