/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:23:05 by axlamber          #+#    #+#             */
/*   Updated: 2023/04/02 19:49:28 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_wall(char c)
{
	return (c == '1' || c == '2' || c == '3' || c == '4');
}

void	get_wall(t_game *game, t_collision *collision, char c)
{
	if (c == '1')
		collision->wall = game->texture.wall1;
	else if (c == '2')
		collision->wall = game->texture.wall2;
	else if (c == '3')
		collision->wall = game->texture.wall3;
	else if (c == '4')
		collision->wall = game->texture.wall4;
	else if (c == 'D')
		collision->wall = game->texture.door;
}

// void wall_render(t_game *game, t_collision collision, t_vector3d line_pos, double line_height)
// {
//     int i;
//     int x_text = 0;
//     int y_text = 0;
//     int pixel_color;
//     int min_i;
//     int max_i;
//     unsigned int *img_addr;
    
//     min_i = (int) fmax(0 , line_pos.y - line_height);
//     max_i = (int) fmin(RES_Y - 1, line_pos.y );
//     float offset = - (line_pos.y - line_height);
//     game->z_buffer[(int) line_pos.x] = collision.distance;
    
//     img_addr = ( unsigned int *)img_get_addr(&game->fps_img, line_pos.x, 0);
//     // Sky
//     i = 0;
// 	while (i < min_i)
//     {
// 		//img_pix_put(&game->fps_img, line_pos.x, i, 0x696969);
//         i++;
//         img_addr += RES_X;
//     }
//     i = min_i;
//     img_addr = ( unsigned int *)img_get_addr(&game->fps_img, line_pos.x, i);
//     while(i < max_i)
//     {
//         if(HD && collision.distance > 1000)
//         {
//             img_pix_put(&game->fps_img, line_pos.x, i, BLACK_PIXEL);
//             i++;
//             img_addr += RES_X;
//             continue;
//         }
//         x_text = (int) (collision.x_pos_tex);
//         y_text = (int) ((i + offset) / line_height * collision.wall.heigth);
//         //printf("pixel %d %d \n", x_text, y_text);
//         pixel_color =  img_pix_read(&collision.wall, x_text, y_text);
        
//         if(HD && collision.distance > 320)
//             pixel_color = add_shade(pixel_color, fmin(fmax(1 - (collision.distance  - 320 ) / 512, 0), 1) * 255) ; 
//         *img_addr = pixel_color; 
//         //img_pix_put(&game->fps_img, line_pos.x, i, pixel_color);
//         img_addr += RES_X;
//         i++;
//     }
// }


void wall_render(t_game *game, t_collision collision, t_vector3d line_pos, double line_height)
{
    int i;
    int x_text = 0;
    int y_text = 0;
    int pixel_color;
    int min_i;
    int max_i;
    
    min_i = (int) fmax(0 , line_pos.y - line_height);
    max_i = (int) fmin(RES_Y - 1, line_pos.y );
    int offset = min_i - (line_pos.y - line_height);

    game->z_buffer[(int) line_pos.x] = collision.distance;
    // Sky
    i = 0;
	while (i < min_i)
    {
		img_pix_put(&game->fps_img, line_pos.x, i, 0x696969);
        i++;
    }
    i = min_i;
    while(i < max_i)
    {
        if(collision.distance > 1000)
        {
            img_pix_put(&game->fps_img, line_pos.x, i, BLACK_PIXEL);
            i++;
            continue;
        }
        x_text = (int) ((collision.x_pos_tex / 64.0f) * collision.wall.width);
        y_text = (int) (((i + offset - min_i) / line_height) * collision.wall.heigth);
        pixel_color =  img_pix_read(&collision.wall, x_text, y_text);
        if(HD && collision.distance > 320)
            pixel_color = add_shade(pixel_color, fmin(fmax(1 - (collision.distance  - 320 ) / 512, 0), 1) * 255) ; 
        // printf("pixel %d %d : %ld\n", x_text, y_text, pixel_color);
        img_pix_put(&game->fps_img, line_pos.x, i, pixel_color);
        i++;
    }
}

void    *start_thread(void *void_game)
{
    t_game *game = (t_game*) void_game; 
    int i; 
    int found_task = 0;
    while(1)
    {
        t_wall_task task;
        pthread_mutex_lock(&game->queue_rights);
        // printf("thread locked queue rights\n");
        if(game->task_done < game->task_count)
        {
            task = game->wall_tasks[game->task_done];
            // i = 0;
            // while(i < RES_X - 1)
            // {
            //     game->wall_tasks[i] = game->wall_tasks[i+1];
            //     i++;
            // }
            found_task = 1;
            game->task_done++;
            if(game->task_done == RES_X - 1)
            {
                pthread_mutex_lock(&game->render_finished_rights);
                game->render_finished = 1;
                pthread_mutex_unlock(&game->render_finished_rights);
            }
        }
        pthread_mutex_unlock(&game->queue_rights);
        if(found_task)
        {
            wall_thread(game, task);
            pre_compute_rows_dist(game, task.line_pos, task.line_height, game->fisheye_resize[(int)  task.line_pos.x]);
            render_floor(game, task.v_ray_dir, task.line_pos);
            render_roof(game, task.v_ray_dir, task.line_pos, task.line_height);
            found_task = 0;
        }
    }
}

void    submit_task_wall(t_game *game, t_wall_task task)
{
    pthread_mutex_lock(&game->queue_rights);
    game->wall_tasks[game->task_count] = task;
    game->task_count++;
    pthread_mutex_unlock(&game->queue_rights);
}

void    wall_thread(t_game *game, t_wall_task d)
{
    int i;
    int x_text = 0;
    int y_text = 0;
    int pixel_color;
    int min_i;
    int max_i;
    
    min_i = (int) fmax(0 , d.line_pos.y - d.line_height);
    max_i = (int) fmin(RES_Y - 1, d.line_pos.y );
    int offset = min_i - (d.line_pos.y - d.line_height);
    i = 0;
	// while (i < min_i)
    // {
	// 	img_pix_put(&game->fps_img, d.line_pos.x, i, 0x696969);
    //     i++;
    // }
    game->z_buffer[(int) d.line_pos.x] = d.collision.distance;
    i = min_i;
    while(i < max_i)
    {
        if(d.collision.distance > 1000)
        {
            // pthread_mutex_lock(&game->img_put_rights);
            img_pix_put(&game->fps_img, d.line_pos.x, i, BLACK_PIXEL);
            // pthread_mutex_unlock(&game->img_put_rights);
            i++;
            continue;
        }
        x_text = (int) ((d.collision.x_pos_tex / 64.0f) * d.collision.wall.width);
        y_text = (int) (((float)(i + offset - min_i) / (float) d.line_height) * d.collision.wall.heigth);
        //  printf("y_text : %f\n", (i + offset - min_i) / d.line_height);
        // pthread_mutex_lock(&game->img_read_rights);
        pixel_color =  img_pix_read(&d.collision.wall, x_text, y_text);
        // pthread_mutex_unlock(&game->img_read_rights);
        if(HD && d.collision.distance > 320)
            pixel_color = add_shade(pixel_color, fmin(fmax(1 - (d.collision.distance  - 320 ) / 512, 0), 1) * 255) ; 
        // printf("pixel %d %d : %ld\n", x_text, y_text, pixel_color);
        // pthread_mutex_lock(&game->img_put_rights);
        img_pix_put(&game->fps_img, d.line_pos.x, i, pixel_color);
        // pthread_mutex_unlock(&game->img_put_rights);
        i++;
    }
}