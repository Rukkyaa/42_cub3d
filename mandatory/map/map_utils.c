/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:32:24 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 14:49:29 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_heigth(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		;
	return (i);
}

// int	map_width(char **map)
// {
// 	return ((int)ft_strlen(map[0]));
// }
