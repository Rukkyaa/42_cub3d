/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:06:10 by theo              #+#    #+#             */
/*   Updated: 2023/03/10 15:10:44 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    sort_imgs(t_img **array)
{
    t_img   *tmp;
    int     sorted;
    int     i;

    if (!array || !*array)
        return ;
    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        i = 0;
        while (array[i + 1])
        {
            if (ft_strncmp(array[i]->name, array[i + 1]->name, ft_strlen(array[i]->name)) > 0)
            {
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                sorted = 0;
            }
            i++;
        }
    }
}