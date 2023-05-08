/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_garbage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:07:24 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/08 14:00:24 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	destroy_img(void)
// {
// 	t_garbage	*gc_img;
// 	t_garbage	*tmp;

// 	gc_img = _gc_img();
// 	while (gc_img)
// 	{
// 		tmp = gc_img;
// 		gc_img = gc_img->next;
// 		if (tmp->content)
// 			mlx_destroy_image(_mlx()->mlx, tmp->content);
// 		free(tmp);
// 	}
// }

void	print_error(int exit_code)
{
	if (exit_code == MLX_CREATION_ERROR)
		printf("\033[1;31m[Error]\033[0;31m Creation of the mlx failed\n\033[0m");
	else if (exit_code == MALLOC_ERROR || exit_code == INIT_MALLOC_ERROR)
		printf("\033[1;31m[Error]\033[0;31m Malloc failed\n\033[0m");
	else if (exit_code == XPM_ERROR)
		printf("\033[1;31m[Error]\033[0;31m XPM file error\n\033[0m");
	else if (exit_code == ADDR_ERROR)
		printf("\033[1;31m[Error]\033[0;31m Address error\n\033[0m");
}

void	free_spe(int exit_code)
{
	if (exit_code > MLX_CREATION_ERROR)
	{
		mlx_destroy_window(_game()->mlx, _game()->fps_win);
		mlx_destroy_image(_game()->mlx, _game()->fps_img.mlx_img);
		mlx_destroy_display(_game()->mlx);
		free(_game()->mlx);
	}
	free_array(_game()->map);
}

void	free_garbage(int exit_code)
{
	t_garbage	*gc;
	t_garbage	*tmp;

	print_error(exit_code);
	gc = _gc();
	// destroy_img();
	free_spe(exit_code);
	while (gc)
	{
		tmp = gc;
		gc = gc->next;
		free(tmp->content);
		free(tmp);
	}
	exit(exit_code);
}
