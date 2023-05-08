/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:00:06 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 10:00:15 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_game *game)
{
	render_fps(game);
	mlx_put_image_to_window(game->mlx, game->fps_win, game->fps_img.mlx_img, 0,
		0);
}