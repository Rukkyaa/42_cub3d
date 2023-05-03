/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:53:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/03 11:16:24 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_xpm_to_img(t_game *game, t_img *img, char *path)
{
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->heigth);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len,
			&img->endian);
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

void	load_buttons(t_game *game)
{
	game->buttons[0].pos.x = 640;
	game->buttons[0].pos.y = 650;
	ft_xpm_to_img(game, &game->buttons[0].idle_img,
		"images/UI/start_button_idle.xpm");
	ft_xpm_to_img(game, &game->buttons[0].hover_img,
		"images/UI/start_button_hover.xpm");
}

void	load_img_two(t_game *game)
{
	ft_xpm_to_img(game, &game->hud.life_orange_bar,
		"images/lifebar/orange_bar.xpm");
	ft_xpm_to_img(game, &game->hud.life_green_bar,
		"images/lifebar/green_bar.xpm");
	ft_xpm_to_img(game, &game->hud.life_bar_border,
		"images/lifebar/grey_border.xpm");
	ft_xpm_to_img(game, &game->texture.projectile,
		"images/projectiles/green_energy_ball.xpm");
	ft_xpm_to_img(game, &game->texture.blue_projectile,
		"images/projectiles/blue_energy_ball.xpm");
	ft_xpm_to_img(game, &game->texture.heart, "images/items/heart/heart.xpm");
	ft_xpm_to_img(game, &game->texture.cocaine, "images/items/cocaine.xpm");
	ft_xpm_to_img(game, &game->texture.menu, "images/UI/menu_cub3D_v2.xpm");
	ft_xpm_to_img(game, &game->texture.player_hurt_overlay,
		"images/FX/blurry_blood.xpm");
	load_number(game);
}

	// ft_xpm_to_img(game, &game->texture.player_hurt_overlay,
	// 	"images/FX/blood_overlay_swapped.xpm");

void	load_img(t_game *game)
{
	ft_xpm_to_img(game, &game->inventory.img, "images/inventory.xpm");
	ft_xpm_to_img(game, &game->weapon_icons.axe, "images/weapons/axe.xpm");
	ft_xpm_to_img(game, &game->weapon_icons.plasma_riffle,
		"images/weapons/icon/plasma_riffle.xpm");
	ft_xpm_to_img(game, &game->weapon_icons.grap_gun,
		"images/weapons/icon/grap_gun.xpm");
	ft_xpm_to_img(game, &game->weapon_icons.shotgun,
		"images/weapons/icon/shotgun.xpm");
	ft_xpm_to_img(game, &game->hud.aim, "images/aim_white_simple.xpm");
	ft_xpm_to_img(game, &game->hud.weapon, "images/weapons/transparent.xpm");
	ft_xpm_to_img(game, &game->hud.life_red_bar, "images/lifebar/red_bar.xpm");
	load_img_two(game);
	load_texture(game);
}
