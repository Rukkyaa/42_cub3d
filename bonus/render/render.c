/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:03:13 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/11 16:21:19 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_life_bar(t_game *game)
{
	t_vector	start;
	t_vector	end;
	int			hp_percentage;

	start.x = RES_X - game->hud.life_red_bar.width - 20;
	start.y = RES_Y - game->hud.life_red_bar.heigth - 10;
	end.x = start.x + (game->hud.life_red_bar.width * game->player.hp
			/ game->player.max_hp);
	end.y = start.y + game->hud.life_red_bar.heigth;
	put_img_to_img(&game->hud.life_bar_border, &game->fps_img, RES_X
		- game->hud.life_bar_border.width - 20, RES_Y
		- game->hud.life_bar_border.heigth - 10);
	hp_percentage = game->player.hp * 100 / game->player.max_hp;
	if (hp_percentage > 66)
		put_img_to_img_crop(&game->hud.life_green_bar, &game->fps_img, start, end);
	else if (hp_percentage > 33)
		put_img_to_img_crop(&game->hud.life_orange_bar, &game->fps_img, start, end);
	else
		put_img_to_img_crop(&game->hud.life_red_bar, &game->fps_img, start, end);

}

void	render_ui(t_game *game)
{
	put_img_to_img(&game->hud.aim, &game->fps_img, game->camera.half_res.x
		- game->hud.aim.width / 2, game->camera.half_res.y
		- game->hud.aim.width / 2);
	put_img_to_img(game->player.weapon->current_img, &game->fps_img, RES_X
		/ 2 - game->player.weapon->current_img->width / 2, RES_Y
		- game->player.weapon->current_img->heigth);
	if (game->inventory_display)
	{
		put_img_to_img(&game->inventory.img, &game->fps_img, 300, 159);
		refresh_inventory(game);
	}
	render_life_bar(game);
}

void	render_map(t_game *game)
{
	render_fps(game);
	// if (game->key_states[2])
	// 	psychedelic_view(game, &game->fps_img);
	// load_map(game);

	sample_img_to_img(&game->minimap, &game->debug_img, game->player.pos.x / 4 - game->minimap_center.x, game->player.pos.y / 4 - game->minimap_center.y );
	draw_filled_circle(&game->minimap, game->minimap_center, 3, RED_PIXEL);
	draw_line_dda(&game->minimap, game->minimap_center, vec_sum(game->minimap_center, vec_scalar_mult(game->player.direction, 10)), RED_PIXEL);	
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
