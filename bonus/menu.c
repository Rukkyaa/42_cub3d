/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:36:02 by teliet            #+#    #+#             */
/*   Updated: 2023/05/03 11:34:28 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	print_fps(int fps)
{
	char	*tmp;

	tmp = ft_itoa(fps);
	mlx_string_put(_mlx()->mlx, _mlx()->win, 100, RES_Y - 20, WHITE_PIXEL, tmp);
	free(tmp);
}

void	handle_button(t_game *game, t_button *button)
{
	if (button->pos.x < game->mouse.x && game->mouse.x < button->pos.x
		+ button->idle_img.width && button->pos.y < game->mouse.y
		&& game->mouse.y < button->pos.y + button->idle_img.heigth)
	{
		put_img_to_img(&button->hover_img, &game->fps_img, button->pos.x,
			button->pos.y);
		if (game->mouse_clicked)
		{
			game->mode = MENU_FADE_OUT;
			game->menu_fade_start = game->frame_count;
			mlx_mouse_hide(game->mlx, _mlx()->win);
		}
	}
	else
		put_img_to_img(&button->idle_img, &game->fps_img, button->pos.x,
			button->pos.y);
}

void	menu_fade_out(t_game *game)
{
	faded_view(game, &game->fps_img, (game->frame_count - game->menu_fade_start)
		* 4);
	if (game->frame_count - game->menu_fade_start > 30)
	{
		game->game_start_time = game->frame_count;
		game->mode = PLAY;
	}
}

void	render_menu(t_game *game)
{
	put_img_to_img(&game->texture.menu, &game->fps_img, 0, 0);
	handle_button(game, &game->buttons[0]);
}
