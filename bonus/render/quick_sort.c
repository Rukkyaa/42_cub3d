/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:20:24 by theo              #+#    #+#             */
/*   Updated: 2023/04/24 14:54:05 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_sprite	*get_tail(t_sprite *cur)
{
	while (cur != NULL && cur->next != NULL)
	{
		cur = cur->next;
	}
	return (cur);
}

t_sprite	*partition(t_sprite *head, t_sprite *end, t_sprite **newHead,
		t_sprite **newEnd)
{
	t_sprite	*pivot;
	t_sprite	*cur;
	t_sprite	*tail;
	t_sprite	*prev;
	t_sprite	*tmp;

	pivot = end;
	prev = NULL;
    cur = head;
    tail = pivot;
	while (cur != pivot)
	{
		if (cur->distance >= pivot->distance)
		{
			if (*newHead == NULL)
			{
				*newHead = cur;
			}
			prev = cur;
			cur = cur->next;
		}
		else
		{
			if (prev != NULL)
			{
				prev->next = cur->next;
			}
			tmp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}
	if (*newHead == NULL)
	{
		*newHead = pivot;
	}
	*newEnd = tail;
	return (pivot);
}

t_sprite	*quick_sort_recur(t_sprite *head, t_sprite *end)
{
	t_sprite	*new_head;
	t_sprite	*new_end;
	t_sprite	*pivot;
	t_sprite	*tmp;

	if (!head || head == end)
	{
		return (head);
	}
	new_head = NULL;
    new_end = NULL;
	pivot = partition(head, end, &new_head, &new_end);
	if (new_head != pivot)
	{
		tmp = new_head;
		while (tmp->next != pivot)
		{
			tmp = tmp->next;
		}
		tmp->next = NULL;
		new_head = quick_sort_recur(new_head, tmp);
		tmp = get_tail(new_head);
		tmp->next = pivot;
	}
	pivot->next = quick_sort_recur(pivot->next, new_end);
	return (new_head);
}

void	sort_sprites(t_sprite **headRef)
{
	*headRef = quick_sort_recur(*headRef, get_tail(*headRef));
}
