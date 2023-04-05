/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:34:34 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/05 10:43:21 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	print_kill(t_game *game, int nb, int x)
{
	if (nb > 9)
		print_kill(game, nb / 10, x - 55);
	put_img_to_img(&game->texture.number[nb % 10], &_mlx()->img, x, 10);
}