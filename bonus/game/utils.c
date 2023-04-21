/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:16:43 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/21 13:52:59 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_key(int keycode)
{
	return ((('a' <= keycode && keycode <= 'z' ) && keycode != 'e' )|| ('0' <= keycode && keycode <= '9' ));
}

bool	is_walkable(t_game *game, int x, int y)
{
	return(!is_wall(game->map[y][x]));
}

bool	player_moving(t_game *game)
{
	
	return (game->key_states['w'] == 1 || game->key_states['a'] == 1
		|| game->key_states['s'] == 1 || game->key_states['d'] == 1);
}

bool	is_collectible(t_game *game)
{
	char	c = game->map[(int)game->player.pos.y / 64]
		[(int)game->player.pos.x / 64];
		
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