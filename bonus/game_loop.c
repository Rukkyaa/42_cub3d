/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/23 16:28:54 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		vec_rotate_edit(&(game->player.direction), -5);
	if (game->key_states[1])
		vec_rotate_edit(&(game->player.direction), 5);
	if (game->key_states['r'])
		game->player.direction_adjust += 5;
	if (game->key_states['f'])
		game->player.direction_adjust -= 5;
}

void	render(t_game *game)
{
	if (game->key_states['w'] || game->key_states['s']
		|| game->key_states['a'] || game->key_states['d']
		|| game->key_states['f'] || game->key_states['r']
		|| game->key_states[0] || game->key_states[1])
	{
		load_map(game);
		load_grid(game);
		clean_map(game);
		clear_img(&game->fps_img);
		render_fps(game);
	}
	draw_player(game, RED_PIXEL);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->fps_win,
		game->fps_img.mlx_img, 0, 0);
}

int	game_loop(void *g)
{
	t_game	*game;

	game = (t_game *) g;
	edit_player_pos(game);
	edit_player_rotate(game);
	usleep(8000);
	render(game);
	return (0);
}
