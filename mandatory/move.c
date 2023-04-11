/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:23:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 14:35:15 by axlamber         ###   ########.fr       */
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
