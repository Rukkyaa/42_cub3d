/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:07 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/31 15:36:41 by axlamber         ###   ########.fr       */
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
void	move_sprites(char **map, t_sprite *sprites, t_player *player)
{
	while (sprites)
	{
		if (sprites->type != MOB || vec_distance(sprites->pos, player->pos)
			< 30 || vec_distance(sprites->pos, player->pos) > 200)
		{
			sprites = sprites->next;
			continue;
		}
		if (sprites->pos.x < player->pos.x && can_move(map,
			sprites->pos.x + 1.5 + sprites->width / 2, sprites->pos.y))
			sprites->pos.x += 1.5;
		else if (sprites->pos.x > player->pos.x && can_move(map,
			sprites->pos.x - 1.5 - sprites->width / 2, sprites->pos.y))
			sprites->pos.x -= 1.5;
		if (sprites->pos.y < player->pos.y && can_move(map,
			sprites->pos.x, sprites->pos.y + 1.5 + sprites->width / 2))
			sprites->pos.y += 1.5;
		else if (sprites->pos.y > player->pos.y && can_move(map,
			sprites->pos.x, sprites->pos.y - 1.5 - sprites->width / 2))
			sprites->pos.y -= 1.5;
		sprites = sprites->next;
	}
}
