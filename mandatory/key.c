/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/16 15:56:53 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_gestion(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	else if (keycode == W)
		move(game, 'N');
	else if (keycode == S)
		move(game, 'S');
	else if (keycode == A)
		move(game, 'W');
	else if (keycode == D)
		move(game, 'E');
	return (0);
}
