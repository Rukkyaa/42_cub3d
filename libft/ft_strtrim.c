/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:59:33 by rukkyaa           #+#    #+#             */
/*   Updated: 2022/11/12 15:40:54 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1 ++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i --;
	return (ft_substr(s1, 0, i + 1));
}
