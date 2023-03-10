/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:23:53 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/09 17:14:19 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_mlx	*_mlx(void)
{
	static t_mlx	*mlx = NULL;

	if (!mlx)
	{
		mlx = malloc(sizeof(t_mlx));
		mlx->mlx = mlx_init();
		
		mlx->win = mlx_new_window(mlx->mlx, RES_X, RES_Y, "cub3d");
		mlx->img.mlx_img = mlx_new_image(mlx->mlx, RES_X, RES_Y);
		mlx->img.addr = mlx_get_data_addr(_mlx()->img.mlx_img,
				&_mlx()->img.bpp, &_mlx()->img.line_len, &_mlx()->img.endian);
		mlx->img.width = RES_X;
		mlx->img.heigth = RES_Y;
	}
	if (!mlx)
		return (NULL);
	return (mlx);
}

