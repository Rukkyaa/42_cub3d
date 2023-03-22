/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:54:20 by teliet            #+#    #+#             */
/*   Updated: 2023/03/22 14:35:22 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>

int	my_list_size(t_list *begin_list)
{
	int	i;

	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}

void	ft_swap_data(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	unsigned int	i;

	if (!begin_list)
		return (NULL);
	i = 0;
	while (begin_list)
	{
		if (i == nbr)
			return (begin_list);
		i++;
		begin_list = begin_list->next;
	}
	return (NULL);
}

void	ft_list_reverse_fun(t_list *begin_list)
{
	int	size;
	int	i;

	i = 0;
	size = my_list_size(begin_list);
	if (!begin_list)
		return ;
	while (i < size / 2)
	{
		ft_swap_data(ft_list_at(begin_list, i), ft_list_at(begin_list, size - i
				- 1));
		i++;
	}
}
