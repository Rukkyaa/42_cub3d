/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:55:15 by teliet            #+#    #+#             */
/*   Updated: 2022/10/04 21:55:18 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
	t_list	*current;

	current = begin_list;
	if (!begin_list)
		return (NULL);
	while (current)
	{
		if (!(*cmp)(current->data, data_ref))
			return (current);
		current = current->next;
	}
	return (NULL);
}
