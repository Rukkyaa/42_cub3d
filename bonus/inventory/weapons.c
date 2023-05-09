/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:24 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/09 10:06:29 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	weapon_in_inventory(t_game *game, int id)
{
	int	i;

	i = -1;
	while (++i < 36)
	{
		if (game->inventory.items[i] == id)
			return (true);
	}
	return (false);
}

t_weapon	*get_weapon(t_game *game, t_inventory *inventory, int id)
{
	if (id > 36)
		return (NULL);
	if (inventory->items[id] == AXE)
		return (&game->weapons.axe);
	else if (inventory->items[id] == PLASMA_RIFFLE)
		return (&game->weapons.plasma_riffle);
	else if (inventory->items[id] == GRAP_GUN)
		return (&game->weapons.grap_gun);
	else if (inventory->items[id] == SHOTGUN)
		return (&game->weapons.shotgun);
	return (NULL);
}

void	inventory_switch(t_game *game)
{
	if (get_weapon(game, &game->inventory,
			game->player.weapon_selected) != game->player.weapon)
	{
		if (get_weapon(game, &game->inventory, game->player.weapon_selected))
			game->player.weapon = get_weapon(game, &game->inventory,
					game->player.weapon_selected);
		else
			game->player.weapon = &game->weapons.axe;
	}
	if (game->key_states['0' + 1] == 1)
		game->player.weapon_selected = 0;
	else if (game->key_states['0' + 2] == 1)
		game->player.weapon_selected = 1;
	else if (game->key_states['0' + 3] == 1)
		game->player.weapon_selected = 2;
	else if (game->key_states['0' + 4] == 1)
		game->player.weapon_selected = 3;
	if (game->key_states['0' + 1] == 1 && get_weapon(game, &game->inventory, 0))
		game->player.weapon = get_weapon(game, &game->inventory, 0);
	else if (game->key_states['0' + 2] == 1 && get_weapon(game,
			&game->inventory, 1))
		game->player.weapon = get_weapon(game, &game->inventory, 1);
	else if (game->key_states['0' + 3] == 1 && get_weapon(game,
			&game->inventory, 2))
		game->player.weapon = get_weapon(game, &game->inventory, 2);
}
