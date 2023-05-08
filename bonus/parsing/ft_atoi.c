/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:11:21 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 17:34:25 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static unsigned int	ft_is_spaces(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static unsigned int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char const *str)
{
	int				sign;
	unsigned int	i;
	long int		result;

	sign = 1;
	i = -1;
	result = 0;
	if (len_num(str) > 11)
		return (0);
	while (ft_is_spaces(str[++i]))
		;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while (ft_is_digit(str[i]))
		result = (result * 10) + str[i++] - '0';
	result *= sign;
	if (result > INT_MAX || result < INT_MIN)
		return (0);
	return (result);
}
