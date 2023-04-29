/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/29 17:54:39 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_walkable(t_game *game, float x, float y)
{
	if (game->map[(int) y][(int) x] == '1')
		return (0);
	return (1);
}

void	player_wall_collides(t_game *game, t_vector speed)
{
	t_vector	v_offset;
	t_vector	vi_pos;
	t_vector	vi_pos_add_offset;

	v_offset.x = 0;
	v_offset.y = 0;
	if (speed.x > 0)
		v_offset.x = 25;
	else
		v_offset.x = -25;
	if (speed.y > 0)
		v_offset.y = 25;
	else
		v_offset.y = -25;
	vi_pos = pixel_to_tile(vec_sum(game->player.pos,game->player.speed));
	vi_pos_add_offset = pixel_to_tile(vec_sum(game->player.pos, v_offset));
	if (!is_walkable(game, vi_pos_add_offset.x, vi_pos.y))
		game->player.speed.x = 0;
	if (!is_walkable(game, vi_pos.x, vi_pos_add_offset.y))
		game->player.speed.y = 0;
}

void	edit_player_pos(t_game *game)
{
	t_vector	right;
	t_vector	left;

	right = vec_rotate(game->player.direction, 90);
	left = vec_rotate(game->player.direction, 270);
	if (game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.direction, 1);
	else if (game->key_states['s'])
		game->player.speed = vec_scalar_mult(game->player.direction, -1);
	if (game->key_states['a'])
	{
		game->player.speed = vec_sum(game->player.speed, left);
		game->player.speed = vec_normalize(game->player.speed);
	}
	else if (game->key_states['d'])
	{
		game->player.speed = vec_sum(game->player.speed, right);
		game->player.speed = vec_normalize(game->player.speed);
	}
	if (game->key_states[2] && game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.speed, 12);
	else
		game->player.speed = vec_scalar_mult(game->player.speed, 6);
	player_wall_collides(game, game->player.speed);
	game->player.pos = vec_sum(game->player.pos, game->player.speed);
	game->player.speed.x = 0;
	game->player.speed.y = 0;
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
