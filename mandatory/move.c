/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:23:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/04 15:41:27 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move(t_game *game, char direction)
{
	if (direction == 'N')
		game->player.pos.y -= 2;
	else if (direction == 'S')
		game->player.pos.y += 2;
	else if (direction == 'W')
		game->player.pos.x -= 2;
	else
		game->player.pos.x += 2;
}
