/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:20:40 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/23 22:06:56 by rukkyaa          ###   ########.fr       */
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
	mlx_destroy_image(_mlx()->mlx, game->weapon.sword.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->weapon.axe.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->hud.aim.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->hud.weapon.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->texture.projectile.mlx_img);
}

void	kill_threads(t_game *game)
{
	int i;

	i = 0;
	while(i < NB_THREADS)
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
	int	i;

	mlx_destroy_window(game->mlx, _mlx()->win);
	mlx_destroy_image(_mlx()->mlx, _mlx()->img.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->debug_img.mlx_img);
	mlx_destroy_image(_mlx()->mlx, game->minimap.mlx_img);
	i = -1;
	while (game->animations.zombie_run.imgs[++i])
	{
		mlx_destroy_image(_mlx()->mlx, game->animations.zombie_run.imgs[i]->mlx_img);
		free(game->animations.zombie_run.imgs[i]);
	}
	free(game->animations.zombie_run.imgs);
	i = -1;
	while (game->hud.weapon_anim.imgs[++i])
	{
		mlx_destroy_image(_mlx()->mlx, game->hud.weapon_anim.imgs[i]->mlx_img);
		free(game->hud.weapon_anim.imgs[i]);
	}
	free(game->hud.weapon_anim.imgs);
	free_imgs(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_array(game->map);
	kill_threads(game);
	free_garbage();
	exit(0);
}
