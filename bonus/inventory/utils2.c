/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:03:38 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/30 15:02:16 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	swap_items(int first, int second, int items[36])
{
	int	tmp;

	tmp = items[first];
	items[first] = items[second];
	items[second] = tmp;
}
