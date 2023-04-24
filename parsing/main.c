/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:48:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/24 18:01:15 by axlamber         ###   ########.fr       */
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
	free_map(parsing->map);
	free(parsing);
	return (EXIT_SUCCESS);
}
