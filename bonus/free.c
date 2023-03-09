/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:20:40 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 17:11:55 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	mlx_destroy_window(game->mlx, _mlx()->win);
	mlx_destroy_image(game->mlx, _mlx()->img.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall1.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall2.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall3.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall4.mlx_img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_array(game->map);
	exit(0);
}
