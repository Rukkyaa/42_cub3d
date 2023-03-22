/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_merge.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:55:34 by teliet            #+#    #+#             */
/*   Updated: 2023/03/22 14:35:22 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>

void	ft_swap_data(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void	my_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;

	if (!begin_list)
		return ;
	current = *begin_list;
	while (current->next)
	{
		if (cmp(current->data, current->next->data) > 0)
		{
			ft_swap_data(current, current->next);
			current = *begin_list;
		}
		else
			current = current->next;
	}
}

t_list	*my_list_last(t_list *begin_list)
{
	if (!begin_list)
		return (NULL);
	while (begin_list->next)
	{
		begin_list = begin_list->next;
	}
	return (begin_list);
}

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list	*last;

	if (!*begin_list1)
	{
		*begin_list1 = begin_list2;
		return ;
	}
	if (!begin_list2)
	{
		if (begin_list1)
			begin_list2 = *begin_list1;
		return ;
	}
	last = my_list_last(*begin_list1);
	last->next = begin_list2;
}

void	ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2,
		int (*cmp)())
{
	ft_list_merge(begin_list1, begin_list2);
	my_list_sort(begin_list1, cmp);
}
