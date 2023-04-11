/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:33:19 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 12:07:56 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	refresh_inventory(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 12)
		{
			if (game->inventory.selected == i * 12 + j)
				continue ;
			if (!strcmp(game->inventory.items[i * 12 + j], "sword"))
				put_img_to_img(&game->weapon_icons.sword, &_mlx()->img, 329 + j * 80, 530 + i * 70);
			if (!strcmp(game->inventory.items[i * 12 + j], "axe"))
				put_img_to_img(&game->weapon_icons.axe, &_mlx()->img, 329 + j * 80, 530 + i * 70);
		}
	}
	if (game->inventory.selected != -1)
	{
		if (item_out_of_bound(game->mouse, game->fps_img,
			*game->inventory.selected_img))
			return ;
		put_img_to_img(game->inventory.selected_img, &game->fps_img,
			game->mouse.x - game->inventory.selected_img->width / 2,
				game->mouse.y - game->inventory.selected_img->heigth / 2);
	}
}
