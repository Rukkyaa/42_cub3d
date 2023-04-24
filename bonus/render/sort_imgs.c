/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:06:10 by theo              #+#    #+#             */
/*   Updated: 2023/04/24 13:57:10 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sort_imgs(t_img **array)
{
	t_img	*tmp;
	int		sorted;
	int		i;

	if (!array || !*array)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (array[i + 1])
		{
			if (strcmp(array[i]->name, array[i + 1]->name) > 0
				|| strlen(array[i]->name) > strlen(array[i + 1]->name))
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}
