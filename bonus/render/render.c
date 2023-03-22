/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:03:13 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/20 17:06:53 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_ui(t_game *game)
{
	put_img_to_img( &game->hud.aim, &game->fps_img, game->camera.half_res.x - game->hud.aim.width / 2, game->camera.half_res.y - game->hud.aim.width / 2);
	update_animation(game , &game->hud.weapon_anim);
	//put_img_to_img( &game->hud.weapon, &game->fps_img, RES_X -  game->hud.weapon.width - RES_X / 2  , RES_Y -  game->hud.weapon.heigth);
	put_img_to_img( game->hud.weapon_anim.current_img, &game->fps_img, RES_X/2 -  game->hud.weapon_anim.current_img->width/2  , RES_Y -  game->hud.weapon_anim.current_img->heigth);
	mlx_string_put(game->mlx, game->fps_win, 100 , RES_Y - 20, WHITE_PIXEL, ft_itoa(game->time.fps));
	if (game->key_states['e'])
	{
		put_img_to_img(&game->inventory.img, &game->fps_img, 300, 159);
		refresh_inventory(game);
	}
}

void	render_map(t_game *game)
{
	render_fps(game);
	// if (game->key_states[2])
	// 	psychedelic_view(game, &game->fps_img);
	// load_map(game);

	sample_img_to_img(&game->minimap, &game->debug_img, game->player.pos.x - 122, game->player.pos.y - 122 );
	draw_filled_circle(&game->minimap, game->minimap_center, 5, RED_PIXEL);
	// draw_player(game, RED_PIXEL);
}

void	render(t_game *game)
{
	// mlx_put_image_to_window(game->mlx, game->debug_win,
	// 	game->debug_img.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->fps_win,
		game->fps_img.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->fps_win,
		game->minimap.mlx_img, 0, 0);
}