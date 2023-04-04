/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/04 13:12:09 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	can_move(char **map, float p_x, float p_y)
{
	int x;
	int y;

	x = (int)(p_x) / 64;
	y = (int)(p_y) / 64;
	if (is_wall(map[y][x]))
		return (false);
	return (true);
}

// Move every sprites to the left
void	move_sprites(char **map, t_sprite *sprites, t_player *player, long delta_frame)
{
	t_sprite	*begin;

	begin = sprites;
	while (sprites)
	{
		if (sprites->type != MOB || vec_distance(sprites->pos, player->pos)
			< 30 || vec_distance(sprites->pos, player->pos) > 400)
		{
			sprites = sprites->next;
			continue;
		}
		sprites->speed = vec_sum(player->pos, vec_scalar_mult(sprites->pos, -1));
		printf("%ld\n", delta_frame);
		sprites->pos = vec_sum(vec_scalar_mult(sprites->speed, (float)delta_frame / 30.0f), sprites->pos);
		printf("2%ld\n", delta_frame);
		sprites->pos.z = -5;
		sprites = sprites->next;
	}
}
