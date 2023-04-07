/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:53 by teliet            #+#    #+#             */
/*   Updated: 2023/04/07 14:57:59 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	respawn_zombie(t_game *game)
{
	t_vector	zombie_pos;
	t_sprite	*tmp;

	while(1)
	{
		zombie_pos.x = (double)rand() / (double)RAND_MAX * map_width(game->map) * 64;
		zombie_pos.y = (double)rand() / (double)RAND_MAX * map_heigth(game->map) * 64;
		if (game->map[(int)zombie_pos.y / 64][(int)zombie_pos.x / 64] == '0')
		{
			tmp = spawn_zombie(game, zombie_pos);
			if (!tmp)
				printf("error spawn zombie\n");
			break ;
		}
	}
}

void    melee_attack(t_game *game, t_weapon *weapon)
{
    t_sprite	*sprite;
    t_sprite	*next_sprite;
    
    sprite = game->sprites;
    while(sprite)
    { 
        next_sprite = sprite->next;
        if(sprite->type == MOB && sprite->visible && sprite->state != DEATH && sprite->state != SPAWN)
        {
            if(fabs(sprite->angle_to_player) < M_PI / 4 && sprite->distance < 45)
			{
                sprite->hp -= weapon->damage;
				if (sprite->hp <= 0)
				{
					game->player.kills++;
					respawn_zombie(game);
					respawn_zombie(game);
				}
			}
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