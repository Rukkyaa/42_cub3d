/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/27 15:21:11 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	if(game->map[(int) tile_coord.y][(int) tile_coord.x] == '1')
		return (0);
	return (1);
}

t_vector	vec_resize(t_vector vec1, double i)
{
	t_vector	v_resized;

	v_resized = vec_normalize(vec1);
	v_resized = vec_scalar_mult(v_resized, i);
	return (v_resized);
}


int		player_collides(t_game *game, t_vector speed)
{
	t_vector plane_pos = vec_sum(game->player.pos,vec_resize(speed, game->camera.proj_plane_distance)); //vec_sum(game->player.pos, vec_scalar_mult(game->player.direction, game->camera.proj_plane_distance));
	// vec_print(&plane_pos, "plane_pos");
	t_vector next_pos = vec_sum(speed, plane_pos);
	t_vector next_tile = pixel_to_tile(next_pos);
	// vec_print(&game->player.pos, "player.pos");
	// vec_print(&next_pos, "next_pos");
	// vec_print(&next_tile, "next_tile");
	draw_filled_circle(&game->img, next_pos, 10, BLUE_PIXEL);
	//game->map[(int) next_tile.y][(int) next_tile.x] = 'B';
	return(!is_walkable(game, next_tile));
}

void	edit_player_pos(t_game *game)
{
	t_vector right = vec_rotate(game->player.direction, 90);
	t_vector left = vec_rotate(game->player.direction, 270);
	if (game->key_states['w'] )
		game->player.speed = vec_scalar_mult(game->player.direction, 1);
	else if (game->key_states['s'] )
		game->player.speed = vec_scalar_mult(game->player.direction, -1);
	if (game->key_states['a'])
	{
		game->player.speed = vec_sum(game->player.speed, left);
		game->player.speed = vec_normalize(game->player.speed);
		// game->player.speed = vec_scalar_mult(game->player.direction, 4);
		// game->player.speed  = vec_sum(game->player.pos,
		// 		vec_scalar_mult(game->player.direction, 4));
		// vec_rotate_edit(&(game->player.direction), 90);
	}
	else if (game->key_states['d'])
	{
		game->player.speed = vec_sum(game->player.speed, right);
		game->player.speed = vec_normalize(game->player.speed);
		// vec_rotate_edit(&(game->player.direction), 90);
		// game->player.pos = vec_sum(game->player.pos,
		// 		vec_scalar_mult(game->player.direction, 4));
		// vec_rotate_edit(&(game->player.direction), 270);
	}
	if(game->key_states[2] && game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.speed, 6);
	else
		game->player.speed = vec_scalar_mult(game->player.speed, 4);
	if(!player_collides(game, game->player.speed))
		game->player.pos = vec_sum(game->player.pos, game->player.speed);
	game->player.speed.x = 0;
	game->player.speed.y = 0;
}

void	edit_player_rotate(t_game *game)
{
	if (game->key_states[0])
	{
		vec_rotate_edit(&(game->player.direction), -3);
	}
	if (game->key_states[1])
		vec_rotate_edit(&(game->player.direction), 3);
	if (game->key_states['r'])
		game->player.direction_adjust += 0.01;
	if (game->key_states['f'])
		game->player.direction_adjust -= 0.01;
}

void	render_map(t_game *game)
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

}

void	render(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->fps_win,
		game->fps_img.mlx_img, 0, 0);
}

int	player_moving(t_game *game)
{
	
	return (game->key_states['w'] == 1 || game->key_states['a'] == 1
		|| game->key_states['s'] == 1 || game->key_states['d'] == 1);
}

int	game_loop(void *g)
{
	t_game	*game;

	game = (t_game *) g;
	render_map(game);
	if (!player_moving(game))
	{
		ma_device_stop(&game->sounds.footstep.device);
		printf("");
	}
	if (game->key_states['w'] || game->key_states['s']
		|| game->key_states['a'] || game->key_states['d']
		|| game->key_states['f'] || game->key_states['r']
		|| game->key_states[0] || game->key_states[1])
	{
		edit_player_pos(game);
		edit_player_rotate(game);		
	}
	render(game);
	//usleep(16000);
	return (0);
}
