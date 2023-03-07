/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:33:19 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/07 16:18:07 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	refresh_inventory(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->fps_win,
			game->weapon.sword.mlx_img, 321 + 8, 371+159);
}
