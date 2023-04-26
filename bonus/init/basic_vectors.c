/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:19:45 by theo              #+#    #+#             */
/*   Updated: 2023/04/26 12:20:20 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_basic_vectors(t_game *game)
{
	game->v_left.x = -1;
	game->v_left.y = 0;
	game->v_left.z = 0;
	game->v_right.x = 1;
	game->v_right.y = 0;
	game->v_right.z = 0;
	game->v_up.x = 0;
	game->v_up.y = -1;
	game->v_up.z = 0;
	game->v_down.x = 0;
	game->v_down.y = 1;
	game->v_down.z = 0;
}
