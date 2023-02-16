/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:20:15 by rukkyaa           #+#    #+#             */
/*   Updated: 2022/11/12 16:16:31 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	index;
	char	*dest2;
	char	*src2;

	index = 0;
	dest2 = (char *)dest;
	src2 = (char *)src;
	if (n == 0 || dest == src)
		return (dest);
	while (index < n)
	{
		dest2[index] = src2[index];
		index++;
	}
	return (dest);
}
