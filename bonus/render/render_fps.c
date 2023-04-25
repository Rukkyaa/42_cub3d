/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/04/25 17:32:53 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_tasks(t_game *game)
{
	pthread_mutex_lock(&game->queue_rights);
	game->task_count = 0;
	game->task_done = 0;
	game->render_finished = 0;
	pthread_mutex_unlock(&game->queue_rights);
}

t_wall_task	init_task(t_collision collision, float line_height,
		t_vector3d line_pos, t_vector3d v_ray_dir)
{
	t_wall_task	wall_task;

	wall_task.collision = collision;
	wall_task.line_height = line_height;
	wall_task.line_pos = line_pos;
	wall_task.v_ray_dir = v_ray_dir;
	return (wall_task);
}

void	close_tasks(t_game *game)
{
	int	all_tasks_ended;

	all_tasks_ended = 0;
	while (1)
	{
		pthread_mutex_lock(&game->queue_rights);
		if (game->task_done >= RES_X - 1)
			all_tasks_ended = 1;
		pthread_mutex_unlock(&game->queue_rights);
		if (all_tasks_ended)
			break ;
	}
}

t_vector3d	p_to_midwall(t_game *game, t_collision collision)
{
	t_vector3d	player_to_midwall;

	player_to_midwall.x = collision.distance;
	player_to_midwall.y = game->wall_height / 2 - game->player.pos3d.z;
	player_to_midwall = vec_normalize(player_to_midwall);
	return (player_to_midwall);
}

void	render_fps(t_game *game)
{
	int			line_height;
	t_collision	collision;
	t_vector3d	line_pos;
	t_vector3d	player_to_midwall;
	t_vector3d	v_ray_dir;

	line_pos.y = game->camera.half_res.y;
	line_pos.x = 0;
	init_tasks(game);
	while (line_pos.x < RES_X)
	{
		v_ray_dir = vec_rotate_rad(game->player.direction,
				game->ray_angle[(int)line_pos.x]);
		collision = cast_2D_ray(game, v_ray_dir);
		collision.distance = collision.distance
			* game->fisheye_resize_wall[(int)line_pos.x];
		line_height = game->wall_height * game->camera.p_plane_dist
			/ (collision.distance);
		line_pos.y = (game->camera.plane_center.y) - p_to_midwall(game,
				collision).y * game->camera.p_plane_dist + line_height / 2;
		submit_task_wall(game, init_task(collision, line_height, line_pos,
				v_ray_dir));
		line_pos.x++;
	}
	close_tasks(game);
}
