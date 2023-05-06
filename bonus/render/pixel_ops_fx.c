/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_ops_fx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:43:49 by teliet            #+#    #+#             */
/*   Updated: 2023/05/06 19:41:45 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	img_pix_read_disco(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = (img->addr + (y * img->line_len + x * 4));
	return (*pixel);
}

unsigned int	img_pix_read_dark(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = (img->addr + (y * img->line_len + x * 4));
	return (*pixel);
}
