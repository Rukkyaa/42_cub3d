/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:53:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/04/13 14:23:02 by axlamber         ###   ########.fr       */
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

void	load_number(t_game *game)
{
	ft_xpm_to_img(game, &game->texture.number[0], "images/numbers/0.xpm");
	ft_xpm_to_img(game, &game->texture.number[1], "images/numbers/1.xpm");
	ft_xpm_to_img(game, &game->texture.number[2], "images/numbers/2.xpm");
	ft_xpm_to_img(game, &game->texture.number[3], "images/numbers/3.xpm");
	ft_xpm_to_img(game, &game->texture.number[4], "images/numbers/4.xpm");
	ft_xpm_to_img(game, &game->texture.number[5], "images/numbers/5.xpm");
	ft_xpm_to_img(game, &game->texture.number[6], "images/numbers/6.xpm");
	ft_xpm_to_img(game, &game->texture.number[7], "images/numbers/7.xpm");
	ft_xpm_to_img(game, &game->texture.number[8], "images/numbers/8.xpm");
	ft_xpm_to_img(game, &game->texture.number[9], "images/numbers/9.xpm");
}

void	load_img(t_game *game)
{
	ft_xpm_to_img(game, &game->texture.wall1, "images/retro_texture_pack/CRATE_1L.xpm");
	ft_xpm_to_img(game, &game->texture.wall2, "images/retro_texture_pack/CRATE_1M.xpm");
	ft_xpm_to_img(game, &game->texture.wall3, "images/retro_texture_pack/DOOR_2A.xpm");
	ft_xpm_to_img(game, &game->texture.wall4, "images/retro_texture_pack/CRATE_1J.xpm");
	ft_xpm_to_img(game, &game->texture.door, "images/retro_texture_pack/DOOR_2E.xpm");
	ft_xpm_to_img(game, &game->texture.ground, "images/retro_texture_pack/TILE_3E.xpm");
	ft_xpm_to_img(game, &game->texture.roof, "images/retro_texture_pack/CONCRETE_1A.xpm");
	ft_xpm_to_img(game, &game->inventory.img, "images/inventory.xpm");
	ft_xpm_to_img(game, &game->weapon_icons.sword, "images/weapons/longsword.xpm");
	ft_xpm_to_img(game, &game->weapon_icons.axe, "images/weapons/axe.xpm");
	ft_xpm_to_img(game, &game->hud.aim, "images/aim_white_simple.xpm");
	ft_xpm_to_img(game, &game->hud.weapon, "images/weapons/transparent.xpm");
	ft_xpm_to_img(game, &game->hud.life_red_bar, "images/lifebar/red_bar.xpm");
	ft_xpm_to_img(game, &game->hud.life_orange_bar, "images/lifebar/orange_bar.xpm");
	ft_xpm_to_img(game, &game->hud.life_green_bar, "images/lifebar/green_bar.xpm");
	ft_xpm_to_img(game, &game->hud.life_bar_border, "images/lifebar/grey_border.xpm");
	ft_xpm_to_img(game, &game->texture.projectile, "images/projectiles/green_energy_ball.xpm");
	ft_xpm_to_img(game, &game->texture.blue_projectile, "images/projectiles/blue_energy_ball.xpm");
	ft_xpm_to_img(game, &game->texture.heart, "images/items/heart/heart.xpm");
	load_number(game);
	// ft_xpm_to_img(game, &game->hud.aim, "images/aim_red.xpm");
}
