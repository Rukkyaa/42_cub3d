/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:16:43 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/01 22:32:35 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_walkable(t_game *game, int x, int y)
{
	t_door	*door;

	if (is_wall(game->map[y][x]))
		return (0);
	if (game->map[y][x] == 'D')
	{
		door = game->doors[(int)(y * map_width(game->map) + x)];
		if (door->open_state < 50)
			return (0);
	}
	return (1);
}

bool	player_moving(t_game *game)
{
	return (game->key_states['w'] == 1 || game->key_states['a'] == 1
		|| game->key_states['s'] == 1 || game->key_states['d'] == 1);
}

bool	is_collectible(t_game *game)
{
	char	c;

	c = game->map[(int)game->player.pos.y / 64][(int)game->player.pos.x / 64];
	return (c == 'S' || c == 'A');
}

long	ft_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	update_kill(t_game *game)
{
	game->player.kills++;
	game->current_wave->zombie_killed++;
}
