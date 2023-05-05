/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:13:31 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/05 11:55:47 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_texture(t_game *game)
{
	game->texture.wall1 = create_img("images/retro_texture_pack/CRATE_1L.xpm");
	game->texture.wall2 = create_img("images/retro_texture_pack/CRATE_1M.xpm");
	game->texture.wall3 = create_img("images/retro_texture_pack/DOOR_2A.xpm");
	game->texture.wall4 = create_img("images/retro_texture_pack/CRATE_1J.xpm");
	game->texture.door = create_img("images/retro_texture_pack/DOOR_2E.xpm");
	game->texture.roof = create_img("images/retro_texture_pack/CONCRETE_1A.xpm");
	game->texture.ground = create_img("images/retro_texture_pack/TILE_3E.xpm");
}
