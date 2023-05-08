/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:27:56 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/06 20:46:48 by rukkyaa          ###   ########.fr       */
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
		free_garbage(MALLOC_ERROR);
	}
	tmp = gc_new(memory);
	if (!tmp)
	{
		free(memory);
		free_garbage(MALLOC_ERROR);
	}
	gc_add_back(&gc, tmp);
	return (memory);
}
