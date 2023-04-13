/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:24 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/13 16:16:56 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_weapon	*get_weapon(t_game *game, t_inventory *inventory, int id)
{
	if (id > 36)
		return (NULL);
	if (inventory->items[id] == AXE)
		return (&game->weapons.axe);
	else if (inventory->items[id] == PLASMA_RIFFLE)
		return (&game->weapons.plasma_riffle);
	return (NULL);
}

void	inventory_switch(t_game *game)
{
	if (get_weapon(game, &game->inventory, game->player.weapon_selected) != game->player.weapon)
	{
		if (get_weapon(game, &game->inventory, game->player.weapon_selected))
			game->player.weapon = get_weapon(game, &game->inventory, game->player.weapon_selected);
		else
			game->player.weapon = &game->weapons.axe;
	}
	if (game->key_states['0' + 1] == 1)
		game->player.weapon_selected = 24;
	else if (game->key_states['0' + 2] == 1)
		game->player.weapon_selected = 25;
	else if (game->key_states['0' + 3] == 1)
		game->player.weapon_selected = 26;
	if(game->key_states['0' + 1] == 1 && get_weapon(game, &game->inventory, 24))
		game->player.weapon = get_weapon(game, &game->inventory, 24);
	else if(game->key_states['0' + 2] == 1 && get_weapon(game, &game->inventory, 25))
		game->player.weapon = get_weapon(game, &game->inventory, 25);
	else if(game->key_states['0' + 3] == 1 && get_weapon(game, &game->inventory, 26))
		game->player.weapon = get_weapon(game, &game->inventory, 26);
}