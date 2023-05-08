/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:00 by theo              #+#    #+#             */
/*   Updated: 2023/05/08 10:10:20 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	basic_render(t_game *game, t_collision collision, t_vector line_pos,
		double line_height)
{
	if (collision.orientation == 'S' || collision.orientation == 'N')
		draw_vertical_line_2(&game->fps_img, line_pos, line_height, PALE_BLUE);
	else
		draw_vertical_line_2(&game->fps_img, line_pos, line_height,
			PALE_BLUE_SHADED);
}

t_img	*get_wall_texture(t_game *game, t_collision collision)
{
	if (collision.orientation == 'N')
		return (&game->texture.north);
	else if (collision.orientation == 'S')
		return (&game->texture.south);
	else if (collision.orientation == 'E')
		return (&game->texture.east);
	else if (collision.orientation == 'W')
		return (&game->texture.west);
	return (NULL);
}

void	texture_render(t_game *game, t_collision collision, t_vector line_pos,
		double line_height)
{
	int	i;
	int	x_text;
	int	y_text;
	int	pixel_color;

	i = -1;
	x_text = 0;
	y_text = 0;
	while (++i < line_pos.y)
		img_pix_put(&game->fps_img, line_pos.x, i, game->texture.sky_color);
	i = 0;
	while (i < line_height)
	{
		x_text = (int)collision.x_pos_tex;
		y_text = (int)((i / line_height) * 64);
		pixel_color = img_pix_read(get_wall_texture(game, collision), x_text,
				y_text);
		img_pix_put(&game->fps_img, line_pos.x, line_pos.y + i, pixel_color);
		i++;
	}
	while (i < RES_Y)
		img_pix_put(&game->fps_img, line_pos.x, line_pos.y + i++,
			game->texture.floor_color);
}

void	update_collision(t_collision *collision, t_game *game,
		t_vector line_pos, float half_width)
{
	t_vector	v_player_to_camera_plane;
	t_vector	v_right;

	v_player_to_camera_plane = vec_scalar_mult(game->player.direction,
			game->player.direction_adjust);
	v_right = vec_normalize(vec_rotate(game->player.direction, 90));
	*collision = cast_2d_ray(game,
			vec_normalize(vec_sum(v_player_to_camera_plane,
					vec_scalar_mult(v_right,
						((2.0f * (float)line_pos.x / (RES_X - 1.0f))
							- 1.0f) * half_width))));
	collision->distance = collision->distance
		* cosf(vec_angle(vec_normalize(vec_sum(v_player_to_camera_plane,
						vec_scalar_mult(v_right, ((2.0f * (float)line_pos.x
									/ (RES_X - 1.0f)) - 1.0f) * half_width))),
				game->player.direction));
}

void	render_fps(t_game *game)
{
	int			i;
	float		line_height;
	t_collision	collision;
	t_vector	line_pos;
	float		half_width;

	half_width = tanf((float)FOV_RADIANS / 2.0f)
		* game->player.direction_adjust;
	line_pos.x = 0;
	i = -1;
	while (++i < RES_X)
	{
		update_collision(&collision, game, line_pos, half_width);
		line_height = (64 / collision.distance) * game->player.direction_adjust;
		line_pos.y = RES_Y / 2 - line_height / 2;
		texture_render(game, collision, line_pos, line_height);
		line_pos.x += RES_X / RES_X;
	}
}
