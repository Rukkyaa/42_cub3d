/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_garbage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:07:24 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/06 20:12:22 by rukkyaa          ###   ########.fr       */
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

void	free_spe(int exit_code)
{
	if (exit_code > MLX_CREATION_ERROR)
	{
		mlx_destroy_display(_mlx()->mlx);
		free(_mlx()->mlx);
	}
	free_array(_game()->map);
}

void	free_garbage(int exit_code)
{
	t_garbage	*gc;
	t_garbage	*tmp;

	gc = _gc();
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