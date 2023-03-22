/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:20:24 by theo              #+#    #+#             */
/*   Updated: 2023/03/22 20:07:03 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_sprite* getTail(t_sprite* cur) {
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}

t_sprite* partition(t_sprite* head, t_sprite* end, t_sprite** newHead, t_sprite** newEnd) {
    t_sprite* pivot = end;
    t_sprite* prev = NULL, *cur = head, *tail = pivot;
 
    while (cur != pivot) {
        if (cur->distance >= pivot->distance) {
            if (*newHead == NULL) {
                *newHead = cur;
            }
            prev = cur;
            cur = cur->next;
        }
        else {
            if (prev != NULL) {
                prev->next = cur->next;
            }
            t_sprite* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if (*newHead == NULL) {
        *newHead = pivot;
    }
    *newEnd = tail;
 
    return pivot;
}

t_sprite* quickSortRecur(t_sprite* head, t_sprite* end) {
    if (!head || head == end) {
        return head;
    }
 
    t_sprite *newHead = NULL, *newEnd = NULL;
 
    t_sprite* pivot = partition(head, end, &newHead, &newEnd);
 
    if (newHead != pivot) {
        t_sprite* tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = NULL;
 
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }
 
    pivot->next = quickSortRecur(pivot->next, newEnd);
 
    return newHead;
}

void sort_sprites(t_sprite** headRef) {
    *headRef = quickSortRecur(*headRef, getTail(*headRef));
}
