/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:55:41 by teliet            #+#    #+#             */
/*   Updated: 2022/10/04 21:55:43 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_swap_data(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;

	if (!*begin_list)
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
