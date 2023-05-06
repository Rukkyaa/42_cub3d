/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:20:40 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/06 16:52:41 by rukkyaa          ###   ########.fr       */
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

void	free_sprites(t_sprite *sprites)
{
	t_sprite	*tmp;

	if (!sprites)
		return ;
	while (sprites)
	{
		tmp = sprites->next;
		free(sprites);
		sprites = tmp;
	}
}

void	kill_threads(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_THREADS)
	{
		pthread_detach(game->wall_threads[i]);
		pthread_cancel(game->wall_threads[i]);
		i++;
	}
	pthread_mutex_destroy(&game->print_rights);
	pthread_mutex_destroy(&game->img_read_rights);
	pthread_mutex_destroy(&game->img_put_rights);
	pthread_mutex_destroy(&game->queue_rights);
	pthread_mutex_destroy(&game->render_finished_rights);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, _mlx()->win);
	mlx_destroy_image(_mlx()->mlx, _mlx()->img.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->debug_img.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->minimap.mlx_img);
	kill_threads(game);
	free_array(game->map);
	free_garbage();
	exit(0);
}
