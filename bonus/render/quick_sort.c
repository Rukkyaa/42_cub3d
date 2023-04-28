/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:20:24 by theo              #+#    #+#             */
/*   Updated: 2023/04/28 18:05:10 by teliet           ###   ########.fr       */
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


static t_sprite	*partition_helper(t_sprite *cur, t_sprite *pivot,
		t_sprite **newHead, t_sprite **newEnd)
{
	t_sprite *tmp;

	if (cur->distance >= pivot->distance)
	{
		if (*newHead == NULL)
			*newHead = cur;
		return (cur->next);
	}
	else
	{
		tmp = cur->next;
		cur->next = NULL;
		(*newEnd)->next = cur;
		*newEnd = cur;
		return (tmp);
	}
}

t_sprite	*partition(t_sprite *head, t_sprite *end, t_sprite **newHead,
		t_sprite **newEnd)
{
	t_sprite *pivot = end;
	t_sprite *tail = pivot;
	t_sprite *prev = NULL;
	t_sprite *cur = head;

	while (cur != pivot)
		cur = partition_helper(cur, pivot, newHead, &tail);

	if (*newHead == NULL)
		*newHead = pivot;
	*newEnd = tail;

	return (pivot);
}


t_sprite	*quick_sort_recur_helper(t_sprite *head, t_sprite *end)
{
	t_sprite	*new_head;
	t_sprite	*new_end;
	t_sprite	*pivot;
	t_sprite	*tmp;

	if (!head || head == end)
		return (head);
	new_head = NULL;
	new_end = NULL;
	pivot = partition(head, end, &new_head, &new_end);
	if (new_head != pivot)
	{
		tmp = new_head;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		new_head = quick_sort_recur_helper(new_head, tmp);
		tmp = get_tail(new_head);
		tmp->next = pivot;
	}
	pivot->next = quick_sort_recur_helper(pivot->next, new_end);
	return (new_head);
}

t_sprite	*quick_sort_recur(t_sprite *head, t_sprite *end)
{
	if (!head || head == end)
		return (head);
	return (quick_sort_recur_helper(head, end));
}

void	sort_sprites(t_sprite **headRef)
{
	*headRef = quick_sort_recur(*headRef, get_tail(*headRef));
}
