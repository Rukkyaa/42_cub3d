/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/27 15:17:50 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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


bool	do_damage(int damage, t_sprite *sprite)
{
	sprite->hp -= damage;
	if (sprite->hp <= 0)
		return (true);
	return (false);
}

void	mob_wall_collide(t_game *game, t_sprite *mob)
{
	t_vector3d	v_offset;
	t_vector3d	vi_pos;
	t_vector3d	vi_pos_add_offset;
	
	v_offset.x = 0;
	v_offset.y = 0;
	if (mob->speed.x > 0)
		v_offset.x = mob->width/2;
	else
		v_offset.x = -mob->width/2;
	if (mob->speed.y > 0)
		v_offset.y = mob->width/2;
	else
		v_offset.y = -mob->width/2;
	vi_pos = pixel_to_tile(mob->pos);
	vi_pos_add_offset = pixel_to_tile(vec_sum(mob->pos, v_offset));
	if(!is_walkable(game, vi_pos_add_offset.x, vi_pos.y))
		mob->speed.x = 0;
	if(!is_walkable(game , vi_pos.x, vi_pos_add_offset.y))
		mob->speed.y = 0;
}


void	mob_mob_collide(t_game *game,  t_sprite *sprite_a,  t_sprite *sprite_b)
{
	t_vector3d	next_pos_a;	
	t_vector3d	next_pos_b;	
	float  distance;

	next_pos_a = vec_sum(sprite_a->pos, sprite_a->speed);
	next_pos_b = vec_sum(sprite_b->pos, sprite_b->speed);
	distance = vec_distance(next_pos_a, next_pos_b);
	if (distance < 10)
	{
		sprite_a->speed.x = 0;
		sprite_b->speed.x = 0;
		sprite_a->speed.y = 0;
		sprite_b->speed.y = 0;
	}
}

void	check_mob_collisions(t_game *game, t_sprite *sprite)
{
	t_sprite		*tmp;

	tmp = sprite->next;
	while (tmp)
	{
		if (tmp->type == MOB)
			mob_mob_collide(game, sprite, tmp);
		tmp = tmp->next;
	}
}

static void	move_mob(t_game *game, t_sprite *sprite, t_player *player)
{

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
			float rand_num = (float)((double)rand() / (double)RAND_MAX);
			if (rand_num <= 0.10)
				spawn_item(game, sprite->pos, HEALTH);
			else if (rand_num > 0.10 && rand_num <= 0.25 && !weapon_in_inventory(game, GRAP_GUN))
				spawn_item(game, sprite->pos, GRAP_GUN);
			else if (rand_num > 0.25 && rand_num <= 0.40 && !weapon_in_inventory(game, PLASMA_RIFFLE))
				spawn_item(game, sprite->pos, PLASMA_RIFFLE);
			else if (rand_num > 0.40 && rand_num <= 0.45 && !game->player.cocaine)
				spawn_item(game, sprite->pos, COCAINE);
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
		sprite->speed = vec_sum(player->pos, vec_scalar_mult(sprite->pos, -1));
		sprite->speed = vec_normalize(sprite->speed);
		sprite->speed = vec_scalar_mult(sprite->speed, sprite->velocity);
		sprite->speed.z = 0;
		mob_wall_collide(game, sprite);
		check_mob_collisions(game, sprite);
		sprite->pos = vec_sum(sprite->pos, sprite->speed);
	}
}

int proj_mob_collide(t_sprite *mob, t_sprite *proj) {
	t_vector3d proj_true_pos;
	// t_vector3d proj_to_mob;
	float straight_dist;
	// proj_to_mob = vec_sum(mob->pos, vec_scalar_mult(proj->pos, -1));

	// float angle = vec_angle(proj->speed, proj_to_mob);
	// float x_y_dist = sinf(angle) * vec_distance(mob->pos, proj->pos);
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
		if (tmp->type == MOB && proj_mob_collide(tmp, proj) && tmp->hp > 0)
		{
			if (do_damage(proj->damage + game->player.bonus_strength, tmp))
				update_kill(game);
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

void	check_remove(t_game *game, t_sprite *fx, t_sprite **sprites)
{
	int	time_elapsed_ms;

	time_elapsed_ms = (game->time.frame.tv_sec * 1000
			+ game->time.frame.tv_usec / 1000) - fx->animation.start_time_ms;
	if(time_elapsed_ms > fx->animation.frame_duration_ms * fx->animation.nb_imgs)
		remove_entity(sprites, fx);
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
		else if (tmp->type == FX)
			check_remove(game, tmp, sprites);
		tmp = tmp->next;
	}
}
