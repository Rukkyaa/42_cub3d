/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:27:56 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/05 23:41:46 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_garbage	*gc_new(void *content)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	if (!node)
	{
		printf("GC creation error !\n");
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}

void	gc_add_back(t_garbage **gc, t_garbage *new)
{
	t_garbage	*tmp;

	tmp = *gc;
	if (!tmp)
	{
		*gc = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	*my_alloc(int size)
{
	t_garbage	*gc;
	t_garbage	*tmp;
	void		*memory;

	gc = _gc();
	memory = malloc(size);
	if (!memory)
	{
		printf("Malloc failed !\n");
		free_garbage();
	}
	tmp = gc_new(memory);
	if (!tmp)
	{
		free(memory);
		free_garbage();
	}
	gc_add_back(&gc, tmp);
	return (memory);
}

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

void	free_garbage(void)
{
	t_garbage	*gc;
	t_garbage	*tmp;

	gc = _gc();
	destroy_img();
	while (gc)
	{
		tmp = gc;
		gc = gc->next;
		free(tmp->content);
		free(tmp);
	}
	// exit(0);
}
