/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:31:27 by theo              #+#    #+#             */
/*   Updated: 2023/04/27 19:16:26 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	sample_img(t_img *img, float x, float y)
{
	return (img_pix_read(img, x * img->width, y * img->heigth));
}

void	put_sprite_img(t_game *game, t_sprite *sprite, t_vector3d start_pos,
		t_vector3d end_pos)
{
	float	i;
	float	j;
	float	i_offset;
	float	j_offset;
	int		pixel_color;

	i = start_pos.x - 1;
	j = start_pos.y;
	i_offset = sprite->screen_pos.x - (sprite->screen_size.x / 2);
	j_offset = sprite->screen_pos.y - sprite->screen_size.y;
	while (++i < end_pos.x)
	{
		if (game->z_buffer[(int)i] >= sprite->distance)
		{
			j = start_pos.y - 1;
			while (++j < end_pos.y)
			{
				pixel_color = sample_img(sprite->animation.current_img, (i
							- i_offset) / sprite->screen_size.x, (j - j_offset)
						/ sprite->screen_size.y);
				if (get_t(pixel_color) == 0)
					img_pix_put(&game->fps_img, i, j, pixel_color);
			}
		}
	}
}

void	draw_sprite(t_game *game, t_sprite *sprite)
{
	t_vector3d	start_pos;
	t_vector3d	end_pos;

	sprite->screen_size.y = (sprite->height / sprite->distance)
		* game->camera.p_plane_dist;
	sprite->screen_size.x = (sprite->width / sprite->distance)
		* game->camera.p_plane_dist;
	start_pos.x = fmax(sprite->screen_pos.x - sprite->screen_size.x / 2, 0);
	start_pos.y = fmax(sprite->screen_pos.y - sprite->screen_size.y, 0);
	end_pos.x = fmin(sprite->screen_pos.x + sprite->screen_size.x / 2, RES_X
			- 1);
	end_pos.y = fmin(sprite->screen_pos.y, RES_Y - 1);
	put_sprite_img(game, sprite, start_pos, end_pos);
}

void	compute_sprite(t_game *game, t_sprite *sprite)
{
	t_vector3d	player_to_sprite;
	t_vector3d	screen_pos;
	float		angle;
	float		xy_distance;

	player_to_sprite.x = sprite->pos.x - game->player.pos.x;
	player_to_sprite.y = sprite->pos.y - game->player.pos.y;
	angle = vec_angle(game->player.direction, player_to_sprite);
	sprite->angle_to_player = angle;
	vec_rotate_edit(&player_to_sprite, -game->player.angle);
	xy_distance = sqrt(player_to_sprite.x * player_to_sprite.x
			+ player_to_sprite.y * player_to_sprite.y) * cosf(angle);
	screen_pos.x = (player_to_sprite.y / player_to_sprite.x)
		* ((float)game->camera.p_plane_dist) + RES_X / 2;
	screen_pos.y = game->camera.plane_center.y - (sprite->pos.z
			- game->player.pos3d.z) / xy_distance * game->camera.p_plane_dist;
	sprite->distance = xy_distance;
	sprite->screen_pos = screen_pos;
	if (fabs(angle) > M_PI / 2)
		sprite->visible = 0;
	else
		sprite->visible = 1;
}

void	render_sprites(t_game *game)
{
	t_sprite	*sprite;

	sprite = game->sprites;
	move_sprites(game, &game->sprites, &game->player);
	while (sprite)
	{
		compute_sprite(game, sprite);
		sprite = sprite->next;
	}
	sort_sprites(&game->sprites);
	sprite = game->sprites;
	while (sprite)
	{
		if (sprite->animation.imgs)
			update_animation(game, &sprite->animation);
		if (sprite->visible)
			draw_sprite(game, sprite);
		sprite = sprite->next;
	}
}
