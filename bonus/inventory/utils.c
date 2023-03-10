/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:03:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/10 13:27:18 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_inventory(t_game *game)
{
	int	i;

	i = -1;
	game->inventory.selected = -1;
	while (++i < 36)
		game->inventory.items[i] = "empty";
}

void	add_item(t_game *game, char *str)
{
	int	i;

	i = -1;
	while (++i < 36)
	{
		if (!strcmp(game->inventory.items[i], "empty"))
		{
			game->inventory.items[i] = str;
			return ;
		}
	}
}
