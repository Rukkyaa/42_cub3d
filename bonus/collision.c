/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:56:35 by teliet            #+#    #+#             */
/*   Updated: 2023/02/28 11:55:33 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		is_walkable(t_game *game, t_vector tile_coord)
{
	if(tile_out_of_bound(tile_coord, game))
		return (0);
	if(game->map[(int) tile_coord.y][(int) tile_coord.x] == '1')
		return (0);
    game->map[(int) tile_coord.y][(int) tile_coord.x] = 'B';
	return (1);
}

t_vector get_next_tile(t_game *game, t_vector speed)
{
    t_vector next_tile;
    next_tile.x = 0;
    next_tile.y = 0;
	t_vector current_tile = pixel_to_tile(game->player.pos);
    
	if (speed.x < 0 && !is_walkable(game, vec_sum(current_tile, game->v_left)))
		next_tile.x = -1;
	else if (speed.x > 0 && !is_walkable(game, vec_sum(current_tile, game->v_right)))
		next_tile.x = 1;
	if (speed.y < 0 && !is_walkable(game, vec_sum(current_tile, game->v_up)))
		next_tile.y = -1;
	else if (speed.y > 0 && !is_walkable(game, vec_sum(current_tile, game->v_down)))
		next_tile.y = 1;

    return(next_tile);
}
