/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:55:24 by teliet            #+#    #+#             */
/*   Updated: 2022/10/04 21:55:28 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>

void	remove_first(t_list **begin_list, void (*free_fct)(void *))
{
	t_list	*first;

	first = *begin_list;
	*begin_list = first->next;
	free_fct(first->data);
	free(first);
}

void	remove_element(t_list *last, t_list *elem, void (*free_fct)(void *))
{
	last->next = elem->next;
	free_fct(elem->data);
	free(elem);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
		void (*free_fct)(void *))
{
	t_list	*last;
	t_list	*current;
	t_list	*next;

	last = NULL;
	current = *begin_list;
	while (current)
	{
		if (!(*cmp)(current->data, data_ref))
		{
			next = current->next;
			if (last == NULL)
				remove_first(begin_list, free_fct);
			else
				remove_element(last, current, free_fct);
			current = next;
		}
		else
		{
			last = current;
			current = current->next;
		}
	}
}
