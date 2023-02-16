/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:53:47 by rukkyaa           #+#    #+#             */
/*   Updated: 2022/11/07 10:48:12 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	nb_len(long nb)
{
	unsigned int	len;

	len = 0;
	if (nb < 0)
	{
		len ++;
		nb = -nb;
	}
	else if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long			nb;
	unsigned int	len;
	char			*str;

	nb = n;
	len = nb_len(nb);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		str[len - 1] = nb % 10 + '0';
		nb /= 10;
		len --;
	}
	return (str);
}
