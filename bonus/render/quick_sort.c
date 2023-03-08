/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:20:24 by theo              #+#    #+#             */
/*   Updated: 2023/03/08 20:21:23 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void swap(t_sprite* a, t_sprite* b)
{
    t_sprite temp = *a;
    *a = *b;
    *b = temp;
}

int partition(t_sprite arr[], int low, int high)
{
    float pivot = arr[high].distance;
    int i = low - 1;
 
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].distance <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(t_sprite arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sort_sprites(t_sprite sprites[], int size)
{
    quickSort(sprites, 0, size - 1);
}
