/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/12 14:58:39 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	can_move(char **map, t_vector3d pos)
{
	int	x;
	int	y;

	x = (int)(pos.x) / 64;
	y = (int)(pos.y) / 64;
	if (is_wall(map[y][x]) || ((pos.z < 0 || 64 < pos.z)))
		return (false);
	return (true);
}

static bool	projectile_terrain_collide(char **map, t_sprite *proj)
{
	int	x;
	int	y;

	x = (int)(proj->pos.x + proj->speed.x) / 64;
	y = (int)(proj->pos.y + proj->speed.y) / 64;
	if (is_wall(map[y][x]) || ((proj->pos.z + proj->speed.z + proj->height/2 < 0 || 64 < proj->pos.z + proj->speed.z + proj->height/2)))
		return (false);
	return (true);
}


static bool	do_damage(t_sprite *proj, t_sprite *sprite)
{
	sprite->hp -= 100;
	if (sprite->hp <= 0)
		return (true);
	return (false);
}

static void	move_mob(t_game *game, t_sprite *sprite, t_player *player)
{
	t_vector3d	tmp;
	t_vector3d	start;

	if (sprite->state == SPAWN)
	{
		if (sprite->animation.current_frame > 160)
		{
			sprite->state = RUN;
			sprite->animation =  sprite->animated_mob.run;
			update_start_time(sprite, game);
			update_width(sprite);
			sprite->animation.frame_offset = ((double)rand() / (double)RAND_MAX) * sprite->animation.nb_imgs;
		}
		return ;
	}
	else if (sprite->hp <= 0 || sprite->state == DEATH)
	{
		if (sprite->state != DEATH)
		{
			sprite->state = DEATH;
			sprite->animation =  sprite->animated_mob.death;
			update_start_time(sprite, game);
			update_width(sprite);
		}
		if (sprite->animation.current_frame > 40)
		{
			if (((double)rand() / (double)RAND_MAX) < 0.5)
				spawn_item(game, sprite->pos, "sword", HEALTH);
			remove_entity(&game->sprites, sprite);
		}
	}
	else if (vec_distance(sprite->pos, player->pos) < 30 || sprite->state == ATTACK)
	{
		attack(game, sprite, player);
		return ;
	}
	else
	{
		start = sprite->speed;
		sprite->speed = vec_sum(player->pos, vec_scalar_mult(sprite->pos, -1));
		sprite->speed = vec_normalize(sprite->speed);
		tmp = vec_sum(vec_scalar_mult(sprite->speed, sprite->velocity),
				sprite->pos);
		if (can_move(game->map, tmp))
			sprite->pos = tmp;
	}
}

#include <stdbool.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} t_vector3;

int check_collide(t_sprite *mob, t_sprite *proj) {
	t_vector3d proj_true_pos;
	t_vector3d proj_to_mob;
	float straight_dist;
	proj_to_mob = vec_sum(mob->pos, vec_scalar_mult(proj->pos, -1));

	float angle = vec_angle(proj->speed, proj_to_mob);
	float x_y_dist = sinf(angle) * vec_distance(mob->pos, proj->pos);
	// vec3_print(proj->pos, "proj->pos");

	straight_dist = sqrt((mob->pos.x - proj->pos.x) * (mob->pos.x - proj->pos.x) + (mob->pos.y - proj->pos.y) * (mob->pos.y - proj->pos.y));
	if(straight_dist > sqrt((mob->collide_width/2 + proj->width/2) * (mob->collide_width/2 + proj->width/2)))
		return (0);
	
	proj_true_pos = proj->pos;
	proj_true_pos.z = proj_true_pos.z + proj->width / 2;
	if(proj_true_pos.z > mob->pos.z + mob->height)
		return 0;
		
	return 1;
}

static void	move_proj(t_game *game, t_sprite *proj, t_sprite **sprites)
{
	t_sprite	*tmp;

	tmp = *sprites;
	while (tmp)
	{
		if (tmp->type == PROJ)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type == MOB && check_collide(tmp, proj) && tmp->hp > 0)
		{
			if (do_damage(proj, tmp))
				game->player.kills++;
			remove_entity(sprites, proj);
			return ;
		}
		tmp = tmp->next;
	}
	if (projectile_terrain_collide(game->map, proj))
	{
		proj->last_pos = proj->pos;
		proj->pos = vec_sum(proj->pos, proj->speed);
	}
	else
		remove_entity(sprites, proj);
}

void	move_sprites(t_game *game, t_sprite **sprites, t_player *player)
{
	t_sprite	*tmp;

	tmp = *sprites;
	while (tmp)
	{
		if (tmp->type == MOB)
			move_mob(game, tmp, player);
		else if (tmp->type == PROJ)
			move_proj(game, tmp, sprites);
		tmp = tmp->next;
	}
}
