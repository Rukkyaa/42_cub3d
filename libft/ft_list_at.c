/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:52:29 by teliet            #+#    #+#             */
/*   Updated: 2023/03/22 14:35:34 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_sprite	*ft_list_at(t_sprite *begin_list, unsigned int nbr)
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
