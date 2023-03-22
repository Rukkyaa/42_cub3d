/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:54:20 by teliet            #+#    #+#             */
/*   Updated: 2022/10/04 21:55:03 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list	*last;
	t_list	*current;
	t_list	*next;

	if (!begin_list || !*begin_list)
		return ;
	current = *begin_list;
	last = NULL;
	while (current)
	{
		next = current->next;
		current->next = last;
		last = current;
		current = next;
	}
	*begin_list = last;
}
