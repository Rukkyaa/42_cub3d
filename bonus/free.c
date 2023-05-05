/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:20:40 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/05 23:46:02 by rukkyaa          ###   ########.fr       */
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

void	free_imgs(t_game *game)
{
	mlx_destroy_image(_mlx()->mlx, game->texture.wall1.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.wall2.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.wall3.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.wall4.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.ground.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.roof.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->inventory.img.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->weapon_icons.axe.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->weapon_icons.plasma_riffle.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->hud.aim.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->hud.weapon.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.projectile.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.menu.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->buttons[0].idle_img.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->buttons[0].hover_img.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.player_hurt_overlay.mlx_img);
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
	free_garbage();
	exit(0);
}
