/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:33:19 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/15 12:05:05 by teliet           ###   ########.fr       */
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
			if (!strcmp(game->inventory.items[i * 12 + j], "sword"))
				put_img_to_img(&game->weapon.sword, &_mlx()->img, 329 + j * 80, 530 + i * 70);
			if (!strcmp(game->inventory.items[i * 12 + j], "axe"))
				put_img_to_img(&game->weapon.axe, &_mlx()->img, 329 + j * 80, 530 + i * 70);
		}
	}
}
