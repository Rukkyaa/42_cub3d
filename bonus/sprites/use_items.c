/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:55:35 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/13 17:19:41 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_item(t_game *game)
{
	if (game->player.cocaine)
	{
		if (game->player.start_cocaine + 5000 < ft_now())
		{
			game->player.bonus_strength = 0;
			game->player.cocaine = false;
			game->player.velocity = 100;
		}
		else
		{
			game->player.bonus_strength = 250;
			psychedelic_view(game, &game->fps_img);
			game->player.velocity = 250;
		}
	}
}

bool	is_consommable(t_sprite *item)
{
	return (item->id == HEALTH || item->id == COCAINE);
}

void	use_item(t_game *game, t_sprite *item)
{
	if (item->id == HEALTH)
	{
		game->player.hp += 25;
		if (game->player.hp > game->player.max_hp)
			game->player.hp = game->player.max_hp;
	}
	else if (item->id == COCAINE)
	{
		game->player.cocaine = true;
		game->player.start_cocaine = ft_now();
	}
}