/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   respawn_zombie.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:53 by teliet            #+#    #+#             */
/*   Updated: 2023/04/29 16:52:24 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_zombie_type(void)
{
	float	rand_num;

	rand_num = (float)((double)rand() / (double)RAND_MAX);
	if (rand_num < 0.5)
		return (NORMAL_ZOMBIE);
	else if (rand_num < 0.9)
		return (BABY_ZOMBIE);
	else
		return (BIG_ZOMBIE);
}

void	respawn_zombie(t_game *game)
{
	t_vector3d	zombie_pos;
	t_sprite	*tmp;

	while (1)
	{
		zombie_pos.x = (double)rand() / (double)RAND_MAX * map_width(game->map)
			* 64;
		zombie_pos.y = (double)rand() / (double)RAND_MAX * map_heigth(game->map)
			* 64;
		zombie_pos.z = 0;
		if (game->map[(int)zombie_pos.y / 64][(int)zombie_pos.x / 64] == '0')
		{
			tmp = spawn_zombie(game, zombie_pos, get_zombie_type());
			if (!tmp)
				printf("error spawn zombie\n");
			break ;
		}
	}
}
