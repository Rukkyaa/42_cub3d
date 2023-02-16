/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:20:02 by rukkyaa           #+#    #+#             */
/*   Updated: 2022/11/12 16:10:28 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*content;
	size_t	i;

	i = 0;
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	content = malloc (nmemb * size);
	if (!content)
		return (NULL);
	while (i < nmemb * size)
	{
		((unsigned char *)content)[i] = 0;
		i ++;
	}
	return (content);
}
