/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:53:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/04/27 19:23:44 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_weapon	init_grap_gun(t_game *game)
{
	t_weapon	grap_gun;
	t_animation	grap_gun_anim;

	fill_sprite_animation(game,
		"images/weapons/Grap_gun_upscale_xpm_alpha_resized_fuzz",
		&grap_gun_anim);
	grap_gun_anim.frame_offset = 0;
	grap_gun_anim.start_time_ms = game->time.frame.tv_sec * 1000
		+ game->time.frame.tv_usec / 1000;
	grap_gun.fire_anim = grap_gun_anim;
	grap_gun.idle_img = *grap_gun_anim.imgs;
	grap_gun.cool_down_ms = 1000;
	grap_gun.fire_anim.frame_duration_ms = (int)(grap_gun.cool_down_ms
			/ grap_gun_anim.nb_imgs) + 1;
	grap_gun.attack_speed = 2;
	grap_gun.damage = 200;
	grap_gun.idle_img = grap_gun_anim.imgs[1];
	grap_gun.current_img = grap_gun.idle_img;
	grap_gun.state = IDLE;
	grap_gun.screen_pos.x = 0;
	grap_gun.screen_pos.y = RES_Y - grap_gun.idle_img->heigth;
	grap_gun.is_melee = 0;
	grap_gun.projectile = GREEN_PROJ;
	grap_gun.id = GRAP_GUN;
	return (grap_gun);
}

t_weapon	init_axe(t_game *game)
{
	t_weapon	axe;
	t_animation	axe_anim;

	fill_sprite_animation(game, "images/weapons/axe", &axe_anim);
	axe_anim.frame_duration_ms = 30;
	axe_anim.frame_offset = 0;
	axe_anim.start_time_ms = ft_now();
	game->hud.weapon_anim = axe_anim;
	axe.current_img = axe_anim.imgs[1];
	axe.idle_img = axe_anim.imgs[1];
	axe.screen_pos.x = 0;
	axe.screen_pos.y = 0;
	axe.fire_anim = axe_anim;
	axe.idle_img = *axe_anim.imgs;
	axe.cool_down_ms = 500;
	axe.attack_speed = 2;
	axe.damage = 25;
	axe.state = IDLE;
	axe.is_melee = 1;
	axe.id = AXE;
	return (axe);
}

t_weapon	init_plasma_rifle(t_game *game)
{
	t_weapon	plasma_riffle;
	t_animation	plasma_riffle_anim;

	fill_sprite_animation(game, "images/weapons/plasma_riffle_outscaled",
		&plasma_riffle_anim);
	plasma_riffle_anim.frame_offset = 0;
	plasma_riffle_anim.start_time_ms = game->time.frame.tv_sec * 1000
		+ game->time.frame.tv_usec / 1000;
	plasma_riffle.fire_anim = plasma_riffle_anim;
	plasma_riffle.idle_img = *plasma_riffle_anim.imgs;
	plasma_riffle.cool_down_ms = 100;
	plasma_riffle.fire_anim.frame_duration_ms = (int)(plasma_riffle.cool_down_ms
			/ plasma_riffle_anim.nb_imgs) + 1;
	plasma_riffle.attack_speed = 2;
	plasma_riffle.damage = 10;
	plasma_riffle.idle_img = plasma_riffle_anim.imgs[0];
	plasma_riffle.current_img = plasma_riffle.idle_img;
	plasma_riffle.state = IDLE;
	plasma_riffle.screen_pos.x = 0;
	plasma_riffle.screen_pos.y = RES_Y - plasma_riffle.idle_img->heigth;
	plasma_riffle.is_melee = 0;
	plasma_riffle.projectile = BLUE_PROJ;
	plasma_riffle.id = PLASMA_RIFFLE;
	return (plasma_riffle);
}

void	init_weapons(t_game *game)
{
	game->weapons.grap_gun = init_grap_gun(game);
	game->weapons.plasma_riffle = init_plasma_rifle(game);
	game->weapons.axe = init_axe(game);
	game->player.weapon = &game->weapons.axe;
}
