/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:53:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/03/23 11:08:06 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_xpm_to_img(t_game *game, t_img *img, char *path)
{
	//printf("%s\n", path);
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
		&img->width, &img->heigth);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
}

void	load_img(t_game *game)
{
	// ft_xpm_to_img(&game->texture.wall1, "images/pjay2.xpm");
	ft_xpm_to_img(game, &game->texture.wall1, "images/retro_texture_pack/CRATE_1L.xpm");
	ft_xpm_to_img(game, &game->texture.wall2, "images/retro_texture_pack/CRATE_1M.xpm");
	ft_xpm_to_img(game, &game->texture.wall3, "images/retro_texture_pack/DOOR_2A.xpm");
	ft_xpm_to_img(game, &game->texture.wall4, "images/retro_texture_pack/CRATE_1J.xpm");
	
	// ft_xpm_to_img(game, &game->texture.wall1, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall2, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall3, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall4, "images/SBS_tiny_XPM/Tile/Tile_11-512x512.xpm");
	// ft_xpm_to_img(game, &game->texture.wall1, "images/pjay2.xpm");
	// ft_xpm_to_img(game, &game->texture.wall2,  "images/pjay2.xpm");
	// ft_xpm_to_img(game, &game->texture.wall3,  "images/pjay2.xpm");
	// ft_xpm_to_img(game, &game->texture.wall4,  "images/pjay2.xpm");

	ft_xpm_to_img(game,  &game->texture.ground, "images/retro_texture_pack/TILE_3E.xpm");
	//ft_xpm_to_img(game, &game->texture.roof, "images/retro_texture_pack/WARN_1.xpm");
	// ft_xpm_to_img(game, &game->texture.ground, "images/SBS_tiny_XPM/Tile/Tile_09-512x512.xpm");
	
	ft_xpm_to_img(game,  &game->texture.roof, "images/retro_texture_pack/CONCRETE_1A.xpm");
	ft_xpm_to_img(game, &game->inventory.img, "images/inventory.xpm");
	ft_xpm_to_img(game, &game->weapon.sword, "images/weapons/longsword.xpm");
	ft_xpm_to_img(game, &game->weapon.axe, "images/weapons/axe.xpm");
	ft_xpm_to_img(game, &game->hud.aim, "images/aim_white_simple.xpm");
	// ft_xpm_to_img(game, &game->hud.weapon, "images/weapons/shotgun.xpm");
	ft_xpm_to_img(game, &game->hud.weapon, "images/weapons/transparent.xpm");
	// ft_xpm_to_img(game, &game->texture.projectile, "images/projectile/ball_energy.xpm");
	// ft_xpm_to_img(game, &game->hud.aim, "images/aim_red.xpm");
}
