/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:53 by teliet            #+#    #+#             */
/*   Updated: 2023/04/06 18:02:34 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    melee_attack(t_game *game, t_weapon *weapon)
{
    t_sprite	*sprite;
    t_sprite	*next_sprite;
    
    sprite = game->sprites;
    while(sprite)
    { 
        next_sprite = sprite->next;
        if(sprite->type == MOB && sprite->visible)
        {
            if(fabs(sprite->angle_to_player) < M_PI / 4 && sprite->distance < 45)
                remove_entity(&game->sprites, sprite); 
        }
		sprite = next_sprite;
    }
}

void    handle_weapon(t_game *game, t_weapon *weapon)
{
    
    if(weapon->state == IDLE && game->mouse_clicked == 1)
    {
        weapon->fire_anim.start_time_ms = game->time.frame.tv_sec * 1000 + game->time.frame.tv_usec / 1000;
        weapon->state = FIRE;
        melee_attack(game, weapon);
    }
    if(weapon->state == FIRE)
    {
        int time_elapsed_ms = (game->time.frame.tv_sec * 1000 + game->time.frame.tv_usec / 1000) - weapon->fire_anim.start_time_ms;
        if(time_elapsed_ms >  weapon->fire_anim.frame_duration_ms * weapon->fire_anim.nb_imgs)
        {
            weapon->state = IDLE;
            weapon->current_img =  weapon->idle_img;
        }
        update_animation(game , &weapon->fire_anim);
        weapon->current_img =  weapon->fire_anim.current_img;
    }
    // if(game->mouse_clicked)
	// 	spawn_projectile(game, game->player.pos);
}