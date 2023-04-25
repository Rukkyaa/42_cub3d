/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:15:58 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 17:53:21 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parsing	*parse(char	*map_path)
{
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (NULL);
	parsing->map = get_map(map_path);
	if (!parsing->map)
	{
		free(parsing);
		return (NULL);
	}
	if (!is_map_valid(parsing))
	{
		printf("\nError\nInvalid map\n");
		free_map(parsing->map);
		free(parsing);
		return (NULL);
	}
	printf("Map is valid\n");
	return (parsing);
}
