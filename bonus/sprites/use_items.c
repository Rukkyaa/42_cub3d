/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:55:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 12:08:24 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_consommable(t_sprite *item)
{
	if (item->id == HEALTH)
		return (true);
	return (false);
}

void	use_item(t_game *game, t_sprite *item)
{
	if (item->id == HEALTH)
	{
		game->player.hp += 25;
		if (game->player.hp > game->player.max_hp)
			game->player.hp = game->player.max_hp;
	}
}