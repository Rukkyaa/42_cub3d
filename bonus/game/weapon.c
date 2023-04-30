/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:53 by teliet            #+#    #+#             */
/*   Updated: 2023/04/30 22:16:14 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	melee_attack(t_game *game, t_weapon *weapon)
{
	t_sprite	*sprite;
	t_sprite	*next_sprite;

	sprite = game->sprites;
	while (sprite)
	{
		next_sprite = sprite->next;
		if (sprite->type == MOB && sprite->visible && sprite->state != DEATH
			&& sprite->state != SPAWN)
		{
			if (fabs(sprite->angle_to_player) < M_PI / 4
				&& sprite->distance < 45)
			{
				spawn_blood(game, sprite->pos, 0);
				if (do_damage(weapon->damage + game->player.bonus_strength,
						sprite))
					update_kill(game);
			}
		}
		sprite = next_sprite;
	}
}

void	shotgun_attack(t_game *game, t_weapon *weapon)
{
	t_sprite	*sprite;
	t_sprite	*next_sprite;

	sprite = game->sprites;
	while (sprite)
	{
		next_sprite = sprite->next;
		if (sprite->type == MOB && sprite->visible && sprite->state != DEATH
			&& sprite->state != SPAWN)
		{
			if (sinf(fabs(sprite->angle_to_player)) * sprite->distance < 15)
			{
				spawn_blood(game, sprite->pos, 0);
				if (do_damage(weapon->damage * (240 - sprite->distance) / 240 + game->player.bonus_strength,
						sprite))
					update_kill(game);
			}
		}
		sprite = next_sprite;
	}
}

void	weapon_idle(t_game *game, t_weapon *weapon)
{
	game->player.sound_state.player_shooting = game->player.weapon->id;
	weapon->fire_anim.start_time_ms = ft_now();
	weapon->state = FIRE;
	if(weapon->id == SHOTGUN)
		shotgun_attack(game, weapon);
	else if (weapon->is_melee)
		melee_attack(game, weapon);
	else
		spawn_projectile(game, game->player.pos, weapon->projectile);
}

void	weapon_fire(t_game *game, t_weapon *weapon)
{
	int	time_elapsed_ms;

	time_elapsed_ms = ft_now() - weapon->fire_anim.start_time_ms;
	if (time_elapsed_ms > weapon->fire_anim.frame_duration_ms
		* weapon->fire_anim.nb_imgs)
	{
		weapon->state = IDLE;
		weapon->current_img = weapon->idle_img;
		weapon->fire_anim.current_img = weapon->fire_anim.imgs[0];
		return ;
	}
	update_animation(game, &weapon->fire_anim);
	weapon->current_img = weapon->fire_anim.current_img;
}

void	handle_weapon(t_game *game, t_weapon *weapon)
{
	if (weapon->state == IDLE && game->mouse_clicked == 1)
		weapon_idle(game, weapon);
	else
		game->player.sound_state.player_shooting = 0;
	if (weapon->state == FIRE)
		weapon_fire(game, weapon);
}
