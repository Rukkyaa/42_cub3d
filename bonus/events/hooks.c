/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:08:15 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/06 19:18:02 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	hooks(t_game *game)
{
	mlx_hook(_mlx()->win, 2, 1L << 1, handle_keypress, game);
	mlx_hook(_mlx()->win, 3, 1L << 0, handle_keyrelease, game->key_states);
	mlx_hook(_mlx()->win, 6, 1L << 6, mouse_mouve_hook, game);
	mlx_hook(_mlx()->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(_mlx()->win, 5, 1L << 3, mouse_release, game);
	mlx_hook(_mlx()->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, main_loop, game);
}
