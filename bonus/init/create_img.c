/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:15:40 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/06 20:31:00 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_img	create_img(char *path)
{
	t_garbage	*gc_img;
	t_img		img;

	gc_img = _gc_img();
	img.mlx_img = mlx_xpm_file_to_image(_mlx()->mlx, path,
			&img.width, &img.heigth);
	if (!img.mlx_img)
		free_garbage(XPM_ERROR);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp,
			&img.line_len, &img.endian);
	if (!img.addr)
		free_garbage(ADDR_ERROR);
	gc_add_back(&gc_img, gc_new(img.mlx_img));
	return (img);
}
