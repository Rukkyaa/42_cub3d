/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:20:40 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/23 13:05:03 by rukkyaa          ###   ########.fr       */
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
		tmp = sprites;
		free(sprites);
		sprites = tmp->next;
	}
}

int	close_window(t_game *game)
{
	int	i;

	mlx_destroy_window(game->mlx, _mlx()->win);
	mlx_destroy_image(game->mlx, _mlx()->img.mlx_img);
	i = -1;
	free_sprites(game->sprites);
	while (game->animations.zombie_run.imgs[++i])
	{
		mlx_destroy_image(_mlx()->mlx, game->animations.zombie_run.imgs[i]->mlx_img);
		// printf("Anim : %d\n", i);
	}
	i = -1;
	while (game->hud.weapon_anim.imgs[++i])
	{
		mlx_destroy_image(_mlx()->mlx, game->hud.weapon_anim.imgs[i]->mlx_img);
		// printf("Anim : %d\n", i);
	}
	mlx_destroy_image(_mlx()->mlx, game->weapon.sword.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall1.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall2.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall3.mlx_img);
	mlx_destroy_image(game->mlx, game->texture.wall4.mlx_img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_array(game->map);
	exit(0);
}
