/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/24 17:17:53 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	psychedelic_view(t_game *game, t_img *img)
{
	int	i;
	int	j;
	int	pixel_color;
	printf("%f\n", ((float) (game->time_inc % 300) / 300.0f));
	game->player.direction_adjust = 15 - ((float) (game->time_inc % 300) / 300.0f) * 10.0f;
	i = -1;
	while (++i < RES_X)
	{
		j = -1;
		while (++j < RES_Y)
		{
			pixel_color = img_pix_read(img, i, j) + (game->time_inc % 1000) * 500;
			img_pix_put(img, i, j, pixel_color);
		}
	}
}

int		is_walkable(t_game *game, t_vector tile_coord)
{
	if(tile_out_of_bound(tile_coord, game))
		return (0);
	if(game->map[(int) tile_coord.x][(int) tile_coord.x] == '1')
		return (0);
	return (1);
}

int		check_future_collision(t_game *game, t_vector speed)
{
	t_vector next_tile = pixel_to_tile(vec_sum(vec_sum(speed, game->player.pos), vec_scalar_mult(speed, 1/4 * 20)));

	return(is_walkable(game, next_tile));
}

void	edit_player_pos(t_game *game)
{
	if (game->key_states['w'] )
		game->player.pos = vec_sum(game->player.pos,
				vec_scalar_mult(game->player.direction, 4));
	if (game->key_states['s'] )
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
		// psychedelic_view(game,&game->fps_img);
	}
	game->time_inc++;
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
	usleep(16000);
	render(game);
	return (0);
}
