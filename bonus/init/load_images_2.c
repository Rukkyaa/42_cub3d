/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:13:31 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/03 11:16:11 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_texture(t_game *game)
{
	ft_xpm_to_img(game, &game->texture.wall1,
		"images/retro_texture_pack/CRATE_1L.xpm");
	ft_xpm_to_img(game, &game->texture.wall2,
		"images/retro_texture_pack/CRATE_1M.xpm");
	ft_xpm_to_img(game, &game->texture.wall3,
		"images/retro_texture_pack/DOOR_2A.xpm");
	ft_xpm_to_img(game, &game->texture.wall4,
		"images/retro_texture_pack/CRATE_1J.xpm");
	ft_xpm_to_img(game, &game->texture.door,
		"images/retro_texture_pack/DOOR_2E.xpm");
	ft_xpm_to_img(game, &game->texture.roof,
		"images/retro_texture_pack/CONCRETE_1A.xpm");
	ft_xpm_to_img(game, &game->texture.ground,
		"images/retro_texture_pack/TILE_3E.xpm");
}
