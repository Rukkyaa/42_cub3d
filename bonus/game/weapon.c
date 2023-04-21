/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:53 by teliet            #+#    #+#             */
/*   Updated: 2023/04/21 14:06:03 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_zombie_type(void)
{
	float rand_num = (float)((double)rand() / (double)RAND_MAX);

	if (rand_num < 0.5)
		return (NORMAL_ZOMBIE);
	else if (rand_num < 0.9)
		return (BABY_ZOMBIE);
	else
		return (BIG_ZOMBIE);
}

void	respawn_zombie(t_game *game)
{
	t_vector3d	zombie_pos;
	t_sprite	*tmp;
	while(1)
	{
		zombie_pos.x = (double)rand() / (double)RAND_MAX * map_width(game->map) * 64;
		zombie_pos.y = (double)rand() / (double)RAND_MAX * map_heigth(game->map) * 64;
		zombie_pos.z = 0;
		if (game->map[(int)zombie_pos.y / 64][(int)zombie_pos.x / 64] == '0')
		{
			tmp = spawn_zombie(game, zombie_pos, get_zombie_type());
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
				spawn_blood(game, sprite->pos, 0);
				if (do_damage(weapon->damage + game->player.bonus_strength, sprite))
					update_kill(game);
			}
		}
		sprite = next_sprite;
    }
}

void    handle_weapon(t_game *game, t_weapon *weapon)
{
    if(weapon->state == IDLE && game->mouse_clicked == 1)
    {
		game->player.sound_state.player_shooting = game->player.weapon->id;
        weapon->fire_anim.start_time_ms = ft_now();
        weapon->state = FIRE;
        if(weapon->is_melee)
            melee_attack(game, weapon);
		else
			spawn_projectile(game, game->player.pos, weapon->projectile);
    }
	else
		game->player.sound_state.player_shooting = 0;
    if(weapon->state == FIRE)
    {
        int time_elapsed_ms = ft_now() - weapon->fire_anim.start_time_ms;
		
        if(time_elapsed_ms > weapon->fire_anim.frame_duration_ms * weapon->fire_anim.nb_imgs)
        {
			// if (!weapon->is_melee)
			// 	spawn_projectile(game, game->player.pos);
            weapon->state = IDLE;
            weapon->current_img =  weapon->idle_img;
			weapon->fire_anim.current_img = weapon->fire_anim.imgs[0];
			return ;
        }
        update_animation(game , &weapon->fire_anim);
        weapon->current_img =  weapon->fire_anim.current_img;
    }
}