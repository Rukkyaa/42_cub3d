/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:23:53 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/08 11:18:37 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_mlx	*_mlx(void)
{
	static	t_mlx	*mlx = NULL;

	if (!mlx)
		mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	return (mlx);
}
