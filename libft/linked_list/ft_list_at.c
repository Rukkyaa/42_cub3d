/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:52:29 by teliet            #+#    #+#             */
/*   Updated: 2022/10/04 21:52:32 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

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
