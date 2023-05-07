/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:48:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 13:33:30 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv)
{
	t_parsing	*parsing;

	if (argc != 2)
		return (EXIT_FAILURE);
	parsing = parse(argv[1]);
	if (!parsing)
		return (EXIT_FAILURE);
	// printf("Parsing done\n");
	int i = -1;
	while (parsing->map[++i])
		printf("%s\n", parsing->map[i]);
	free_map(parsing->map);
	free(parsing);
	return (EXIT_SUCCESS);
}
