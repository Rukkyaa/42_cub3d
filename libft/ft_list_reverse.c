/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:54:20 by teliet            #+#    #+#             */
/*   Updated: 2023/03/22 14:35:22 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
