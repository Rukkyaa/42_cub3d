/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:03:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/13 15:23:22 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_inventory(t_game *game)
{
	int	i;

	i = -1;
	game->inventory.selected = -1;
	while (++i < 36)
		game->inventory.items[i] = 0;
}

void	add_item(t_game *game, int id)
{
	int	i;

	i = -1;
	printf("add item %d\n", id);
	while (++i < 36)
	{
		if (game->inventory.items[i] == 0)
		{
			game->inventory.items[i] = id;
			return ;
		}
	}
}

int	get_item(int x, int y, int items[36])
{
	return (items[(y - 530) / 70 * 12 + (x - 321) / 80]);
}

void	select_item(t_game *game, int x, int y)
{
	if (get_item(x, y, game->inventory.items) == AXE)
		game->inventory.selected_img = &game->weapon_icons.axe;
	else if (get_item(x, y, game->inventory.items) == PLASMA_RIFFLE)
		game->inventory.selected_img = &game->weapon_icons.plasma_riffle;
	else
		game->inventory.selected_img = NULL;
}

bool	item_out_of_bound(t_vector3d mouse, t_img img, t_img selected)
{
	return (mouse.x < selected.width / 2 || mouse.x > img.width -
		selected.width / 2 || mouse.y < selected.heigth / 2 || mouse.y
			> img.heigth - selected.heigth / 2);
}
