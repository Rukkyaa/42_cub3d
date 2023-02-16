/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:46:50 by rukkyaa           #+#    #+#             */
/*   Updated: 2022/11/12 15:43:05 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dup;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	dup = ft_strdup(s);
	i = -1;
	if (!dup || !f)
		return (NULL);
	while (dup[++i])
		dup[i] = f(i, dup[i]);
	return (dup);
}
