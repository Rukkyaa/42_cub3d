/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:46:18 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/03 11:49:09 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_shotgun_distance(t_game *game)
{
	int	distance;

	if (game->camera.plane_center.y < game->camera.half_res.y)
		distance = 10 + 240 * (1 - (game->camera.half_res.y
					- game->camera.plane_center.y)
				/ (float)(game->camera.half_res.y - 150));
	else
		distance = 10 + 240 * (1 - (game->camera.plane_center.y
					- game->camera.half_res.y) / (float)(750
					- game->camera.half_res.y));
	return (distance);
}
