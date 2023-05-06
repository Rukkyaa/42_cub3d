/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:50:00 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/06 16:45:27 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_animations(t_game *game)
{
	load_zombie_anim(game);
	game->animations.axe = load_item_anim(game, AXE);
	game->animations.heart = load_item_anim(game, HEALTH);
	game->animations.plasma_riffle = load_item_anim(game, PLASMA_RIFFLE);
	game->animations.cocaine = load_item_anim(game, COCAINE);
	game->animations.grap_gun = load_item_anim(game, GRAP_GUN);
	game->animations.shotgun = load_item_anim(game, SHOTGUN);
}

void	init_sprites(t_game *game)
{
	init_animations(game);
	game->sprites = NULL;
}

void	init_game(t_game *game)
{
	game->mlx = _mlx()->mlx;
	game->frame_count = 0;
	game->time.delta_frame_ms = 0;
	game->time.fps = 0;
	game->wall_height = 64;
	game->mouse_move = 0;
	game->player.kills = 0;
	game->inventory_display = 0;
	game->mouse_clicked = 0;
	game->mouse.x = RES_X / 2;
	game->mouse.y = RES_Y / 2;
	game->mode = MENU;
	game->wave_count = 1;
	game->current_wave = get_wave(game->wave_count);
	game->roof_color = 0x331d0f;
	game->floor_color = 0xb8a386;
	game->doors[3 * map_width(game->map) + 21] = my_alloc(sizeof(t_door));
	game->doors[3 * map_width(game->map) + 21]->pos_x = 21;
	game->doors[3 * map_width(game->map) + 21]->pos_y = 3;
	game->doors[3 * map_width(game->map) + 21]->x_oriented = 1;
	game->doors[3 * map_width(game->map) + 21]->open_state = 0;
	game->doors[3 * map_width(game->map) + 21]->state = CLOSED;
	game->doors[10 * map_width(game->map) + 11] = my_alloc(sizeof(t_door));
	game->doors[10 * map_width(game->map) + 11]->pos_x = 11;
	game->doors[10 * map_width(game->map) + 11]->pos_y = 10;
	game->doors[10 * map_width(game->map) + 11]->x_oriented = 0;
	game->doors[10 * map_width(game->map) + 11]->open_state = 0;
	game->doors[10 * map_width(game->map) + 11]->state = CLOSED;
	game->doors_small[0] = game->doors[3 * map_width(game->map) + 21];
	game->doors_small[1] = game->doors[10 * map_width(game->map) + 11];
	game->doors_small[2] = 0;
}

void	init_keys(t_game *game)
{
	int	i;

	i = 256;
	while (i--)
		game->key_states[i] = 0;
	i = 256;
	while (i--)
		game->key_release_states[i] = 1;
}

void	var_init(t_game *game)
{
	init_keys(game);
	init_basic_vectors(game);
	init_player(game);
	init_game(game);
	init_windows(game);
	init_camera(game, &game->camera);
	precompute_raycast(game);
	pre_compute_resize(game);
	load_img(game);
	load_buttons(game);
	// init_sounds(&game->audio);
	sound_state_init(&game->player.sound_state);
	init_basic_vectors(game);
	init_inventory(game);
	mlx_put_image_to_window(game->mlx, _mlx()->win, _mlx()->img.mlx_img, 0, 0);
	handle_time(game);
	init_sprites(game);
	init_weapons(game);
	load_map_debug(game);
	clear_z_buffer(game);
	init_threads(game);
	load_blood_anim(game);
	spawn_wave(game);
	// free_garbage();
}
