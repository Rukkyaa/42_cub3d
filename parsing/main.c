/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:48:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 18:25:18 by axlamber         ###   ########.fr       */
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
	int i = -1;
	while (parsing->map[++i])
		printf("%s\n", parsing->map[i]);
	free_map(parsing->map);
	free(parsing);
	return (EXIT_SUCCESS);
}
