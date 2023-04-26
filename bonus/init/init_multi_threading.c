/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_threading.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:53:35 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/04/26 12:25:31 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_mutex(t_game *game, pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("pthread_mutex_init error");
		close_window(game);
	}
}

void	init_threads(t_game *game)
{
	int i;

	init_mutex(game, &game->print_rights);
	init_mutex(game, &game->img_read_rights);
	init_mutex(game, &game->img_put_rights);
	init_mutex(game, &game->queue_rights);
	init_mutex(game, &game->render_finished_rights);
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_create(&game->wall_threads[i], NULL, start_thread,
			(void *)game);
		i++;
	}
	pthread_mutex_lock(&game->queue_rights);
	game->render_finished = 0;
	game->task_count = 0;
	game->task_done = 0;
	pthread_mutex_unlock(&game->queue_rights);
}
