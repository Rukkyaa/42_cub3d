/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:57 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/06 11:39:26 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	psychedelic_view(t_game *game, t_img *img)
{
	int	i;
	int	j;
	int	pixel_color;
	printf("%f\n", ((float) (game->time_inc % 300) / 300.0f));
	game->player.direction_adjust = cos(game->time_inc) + 3;
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

t_vector	vec_resize(t_vector vec1, double i)
{
	t_vector	v_resized;

	v_resized = vec_normalize(vec1);
	v_resized = vec_scalar_mult(v_resized, i);
	return (v_resized);
}

static int		is_walkable(t_game *game, int x, int y)
{
	return(!is_wall(game->map[y][x]));
}

void		player_collides(t_game *game, t_vector speed)
{
	t_vector v_offset;
	t_vector vi_pos;
	t_vector vi_pos_add_offset;
	t_vector vi_pos_sub_offset;
	
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

	vi_pos = pixel_to_tile(game->player.pos);
	vi_pos_add_offset = pixel_to_tile(vec_sum(game->player.pos, v_offset));

	if(!is_walkable(game , vi_pos_add_offset.x,  vi_pos.y))
	{
		game->player.speed.x = 0;
	}
	if(!is_walkable(game , vi_pos.x, vi_pos_add_offset.y))
	{
		game->player.speed.y = 0;
	}
}



void	edit_player_pos(t_game *game)
{
	t_vector right = vec_rotate(game->player.direction, 90);
	t_vector left = vec_rotate(game->player.direction, 270);

	if (player_moving(game) && game->key_states[2] == 1)
	{
		ma_device_stop(&game->sounds.footstep.device);
		ma_device_start(&game->sounds.dejavu.device);
	}
	else if (player_moving(game))
	{
		//
		ma_device_start(&game->sounds.footstep.device);
		ma_device_stop(&game->sounds.dejavu.device);
	}
	else
	{
		ma_device_stop(&game->sounds.footstep.device);
		ma_device_stop(&game->sounds.dejavu.device);
	}
	if (game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.direction, 1);
	else if (game->key_states['s'] )
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
	if(game->key_states[2] && game->key_states['w'])
		game->player.speed = vec_scalar_mult(game->player.speed, 10);
	else
		game->player.speed = vec_scalar_mult(game->player.speed, 4);
	player_collides(game, game->player.speed);
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
	render_fps(game);
	if (game->key_states[2])
		psychedelic_view(game, &game->fps_img);
	load_map(game);
	draw_player(game, RED_PIXEL);

}

void	render(t_game *game)
{
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
		ma_device_stop(&game->sounds.footstep.device);
	if (game->key_states['w'] || game->key_states['s']
		|| game->key_states['a'] || game->key_states['d']
		|| game->key_states['f'] || game->key_states['r']
		|| game->key_states[0] || game->key_states[1])
	{
		edit_player_rotate(game);		
	}
	edit_player_pos(game);
	render(game);
	game->time_inc++;
	//usleep(16000);
	return (0);
}
