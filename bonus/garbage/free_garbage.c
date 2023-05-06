/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_garbage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:07:24 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/06 20:43:13 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	destroy_img(void)
{
	t_garbage	*gc_img;
	t_garbage	*tmp;

	gc_img = _gc_img();
	while (gc_img)
	{
		tmp = gc_img;
		gc_img = gc_img->next;
		if (tmp->content)
			mlx_destroy_image(_mlx()->mlx, tmp->content);
		free(tmp);
	}
}

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
		mlx_destroy_window(_mlx()->mlx, _mlx()->win);
		mlx_destroy_image(_mlx()->mlx, _mlx()->img.mlx_img);
		mlx_destroy_image(_mlx()->mlx, _game()->debug_img.mlx_img);
		mlx_destroy_image(_mlx()->mlx, _game()->minimap.mlx_img);
		mlx_destroy_display(_mlx()->mlx);
		free(_mlx()->mlx);
	}
	free_array(_game()->map);
}

void	free_garbage(int exit_code)
{
	t_garbage	*gc;
	t_garbage	*tmp;

	print_error(exit_code);
	gc = _gc();
	if (exit_code > 5)
		kill_threads(_game());
	destroy_img();
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