/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:57:33 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/22 14:59:59 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sprite_add_back(t_sprite **lst, t_sprite *new)
{
	t_sprite  *tmp;

	if (*lst)
	{
		tmp = sprite_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}
