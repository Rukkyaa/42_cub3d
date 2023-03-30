/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:03:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/31 00:22:42 by rukkyaa          ###   ########.fr       */
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

void	add_item(t_game *game, char *type)
{
	int	i;

	i = -1;
	while (++i < 36)
	{
		if (!strcmp(game->inventory.items[i], "empty"))
		{
			game->inventory.items[i] = type;
			return ;
		}
	}
}

char	*get_item(int x, int y, char *items[36])
{
	return (items[(y - 530) / 70 * 12 + (x - 321) / 80]);
}

void	select_item(t_game *game, int x, int y)
{
	if (!strcmp(get_item(x, y, game->inventory.items), "sword"))
		game->inventory.selected_img = &game->weapon.sword;
	else if (!strcmp(get_item(x, y, game->inventory.items), "axe"))
		game->inventory.selected_img = &game->weapon.axe;
}

bool	item_out_of_bound(t_vector3d mouse, t_img img, t_img selected)
{
	return (mouse.x < selected.width / 2 || mouse.x > img.width -
		selected.width / 2 || mouse.y < selected.heigth / 2 || mouse.y
			> img.heigth - selected.heigth / 2);
}
