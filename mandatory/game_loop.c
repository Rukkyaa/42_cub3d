/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 14:57:38 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_walkable(t_game *game, t_vector tile_coord)
{
	if (game->map[(int) tile_coord.x][(int) tile_coord.x] == '1')
		return (0);
	return (1);
}

int	check_future_collision(t_game *game, t_vector speed)
{
	t_vector	next_tile;

	next_tile = pixel_to_tile(vec_sum(vec_sum(speed, game->player.pos),
				vec_scalar_mult(speed, 1 / 4 * 20)));
	return (is_walkable(game, next_tile));
}

void	edit_player_pos(t_game *game)
{
	if (game->key_states['w'])
		game->player.pos = vec_sum(game->player.pos,
				vec_scalar_mult(game->player.direction, 4));
	if (game->key_states['s'])
		game->player.pos = vec_sum(game->player.pos,
				vec_scalar_mult(game->player.direction, -4));
	if (game->key_states['a'])
	{
		vec_rotate_edit(&(game->player.direction), 270);
		game->player.pos = vec_sum(game->player.pos,
				vec_scalar_mult(game->player.direction, 4));
		vec_rotate_edit(&(game->player.direction), 90);
	}
	if (game->key_states['d'])
	{
		vec_rotate_edit(&(game->player.direction), 90);
		game->player.pos = vec_sum(game->player.pos,
				vec_scalar_mult(game->player.direction, 4));
		vec_rotate_edit(&(game->player.direction), 270);
	}
}

void	edit_player_rotate(t_game *game)
{
	if (game->key_states[0])
	{
		vec_rotate_edit(&(game->player.direction), -5);
	}
	if (game->key_states[1])
		vec_rotate_edit(&(game->player.direction), 5);
	if (game->key_states['r'])
		game->player.direction_adjust += 0.1;
	if (game->key_states['f'])
		game->player.direction_adjust -= 0.1;
}

void	render(t_game *game)
{
	render_fps(game);
	mlx_put_image_to_window(game->mlx, game->fps_win,
		game->fps_img.mlx_img, 0, 0);
}

int	game_loop(void *g)
{
	t_game	*game;

	game = (t_game *) g;
	edit_player_pos(game);
	edit_player_rotate(game);
	usleep(16000);
	render(game);
	return (0);
}
