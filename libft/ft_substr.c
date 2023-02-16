/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:47:54 by rukkyaa           #+#    #+#             */
/*   Updated: 2022/11/12 15:39:05 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc_substr(unsigned int start, size_t len, size_t lenstr)
{
	char	*substr;

	if (start > lenstr)
	{
		substr = malloc(1);
		substr[0] = '\0';
		return (substr);
	}
	else if (start + len > lenstr)
		substr = malloc((lenstr - start + 1) * sizeof(char));
	else
		substr = malloc((len + 1) * sizeof(char));
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	lenstr;
	char	*substr;

	if (!s)
		return (NULL);
	lenstr = ft_strlen(s);
	substr = ft_malloc_substr(start, len, lenstr);
	if (!substr)
		return (NULL);
	j = 0;
	while (start < lenstr && j < len)
		substr[j ++] = s[start ++];
	substr[j] = '\0';
	return (substr);
}
