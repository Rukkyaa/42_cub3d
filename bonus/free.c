/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:20:40 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/24 14:36:43 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_array(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->fps_win);
	mlx_destroy_image(game->mlx, game->fps_img.mlx_img);
	mlx_destroy_image(game->mlx, game->img.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall.mlx_img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_array(game->map);
	exit(0);
}
