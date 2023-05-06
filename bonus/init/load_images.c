/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:53:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/06 19:20:34 by rukkyaa          ###   ########.fr       */
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
	game->texture.number[0] = create_img("images/numbers/0.xpm");
	game->texture.number[1] = create_img("images/numbers/1.xpm");
	game->texture.number[2] = create_img("images/numbers/2.xpm");
	game->texture.number[3] = create_img("images/numbers/3.xpm");
	game->texture.number[4] = create_img("images/numbers/4.xpm");
	game->texture.number[5] = create_img("images/numbers/5.xpm");
	game->texture.number[6] = create_img("images/numbers/6.xpm");
	game->texture.number[7] = create_img("images/numbers/7.xpm");
	game->texture.number[8] = create_img("images/numbers/8.xpm");
	game->texture.number[9] = create_img("images/numbers/9.xpm");
}

void	load_buttons(t_game *game)
{
	game->buttons[0].pos.x = 640;
	game->buttons[0].pos.y = 650;
	game->buttons[0].idle_img = create_img("images/UI/start_button_idle.xpm");
	game->buttons[0].hover_img = create_img("images/UI/start_button_hover.xpm");
}

void	load_img_two(t_game *game)
{
	game->hud.life_orange_bar = create_img("images/lifebar/orange_bar.xpm");
	game->hud.life_green_bar = create_img("images/lifebar/green_bar.xpm");
	game->hud.life_bar_border = create_img("images/lifebar/grey_border.xpm");
	game->texture.projectile
		= create_img("images/projectiles/green_energy_ball.xpm");
	game->texture.blue_projectile
		= create_img("images/projectiles/blue_energy_ball.xpm");
	game->texture.heart = create_img("images/items/heart/heart.xpm");
	game->texture.cocaine = create_img("images/items/cocaine.xpm");
	game->texture.menu = create_img("images/UI/menu_cub3D_v2.xpm");
	game->texture.player_hurt_overlay
		= create_img("images/FX/blurry_blood.xpm");
	load_number(game);
}

	// ft_xpm_to_img(game, &game->texture.player_hurt_overlay,
	// 	"images/FX/blood_overlay_swapped.xpm");

void	load_img(t_game *game)
{
	game->inventory.img = create_img("images/inventory.xpm");
	game->weapon_icons.axe = create_img("images/weapons/axe.xpm");
	game->weapon_icons.plasma_riffle
		= create_img("images/weapons/icon/plasma_riffle.xpm");
	game->weapon_icons.grap_gun
		= create_img("images/weapons/icon/grap_gun.xpm");
	game->weapon_icons.shotgun = create_img("images/weapons/icon/shotgun.xpm");
	game->hud.aim = create_img("images/aim_white_simple.xpm");
	game->hud.weapon = create_img("images/weapons/transparent.xpm");
	game->hud.life_red_bar = create_img("images/lifebar/red_bar.xpm");
	load_img_two(game);
	load_texture(game);
}
