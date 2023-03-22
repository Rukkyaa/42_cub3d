/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:02:51 by teliet            #+#    #+#             */
/*   Updated: 2023/03/22 14:36:18 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_list_clear(t_sprite *begin_list, void (*free_fct)(void *))
{
	t_sprite	*temp;

	if (!begin_list)
		return ;
	while (begin_list)
	{
		temp = begin_list;
		begin_list = begin_list->next;
		free_fct(temp);
		free(temp);
	}
}
