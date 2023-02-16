/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:25 by axlamber          #+#    #+#             */
/*   Updated: 2022/11/12 15:51:36 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	if (!dest && size == 0)
		return (0);
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size < destlen || size == 0)
		return (srclen + size);
	while (src[i] && i + destlen < size - 1)
	{
		dest[destlen + i] = src[i];
		i ++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
