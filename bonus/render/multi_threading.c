
#include "cub3d_bonus.h"


void	execute_task(t_game *game, t_wall_task *task)
{
	wall_thread(game, *task);
	pre_compute_rows_dist(game, task->line_pos, task->line_height,
		game->fisheye_resize[(int)task->line_pos.x]);
	render_floor(game, task->v_ray_dir, task->line_pos);
	render_roof(game, task->v_ray_dir, task->line_pos, task->line_height);
}

void	*start_thread(void *void_game)
{
	t_game		*game;
	t_wall_task	task;
	int			found_task;

	game = (t_game *)void_game;
	found_task = 0;
	while (1)
	{
		pthread_mutex_lock(&game->queue_rights);
		if (game->task_done < game->task_count)
		{
			task = game->wall_tasks[game->task_done];
			found_task = 1;
			game->task_done++;
		}
		pthread_mutex_unlock(&game->queue_rights);
		if (found_task)
		{
            execute_task(game, &task);
			found_task = 0;
		}
	}
}

void	submit_task_wall(t_game *game, t_wall_task task)
{
	pthread_mutex_lock(&game->queue_rights);
	game->wall_tasks[game->task_count] = task;
	game->task_count++;
	pthread_mutex_unlock(&game->queue_rights);
}
