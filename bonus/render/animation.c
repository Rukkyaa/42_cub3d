/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:59:39 by theo              #+#    #+#             */
/*   Updated: 2023/03/18 13:48:03 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    update_animation(t_game *game, t_animation *animation)
{
    if(animation->nb_imgs == 1)
        return ;
    int time_elapsed_ms = (game->time.frame.tv_sec * 1000 + game->time.frame.tv_usec / 1000) - animation->start_time_ms; 
    int img_index = (time_elapsed_ms / animation->frame_duration_ms + animation->frame_offset) % animation->nb_imgs;
    // printf("animation_start : %ld\n", animation->start_time_ms);
    // printf("time_elapsed_ms : %d\n", time_elapsed_ms);
    // printf("img_index : %d\n", img_index);
    animation->current_img = animation->imgs[img_index];
}