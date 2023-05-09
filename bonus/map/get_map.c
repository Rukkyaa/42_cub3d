/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:16:26 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/09 13:35:32 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

// static char	*ft_strjoin_free(char *s1, char *s2)
// {
// 	char			*strjoin;
// 	unsigned int	i;
// 	unsigned int	j;

// 	i = 0;
// 	j = 0;
// 	strjoin = my_alloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!strjoin)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		strjoin[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		strjoin[j + i] = s2[j];
// 		j++;
// 	}
// 	strjoin[ft_strlen(s1) + ft_strlen(s2)] = '\0';
// 	return (strjoin);
// }

char	**random_wall(char **s)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	srand(time(NULL));
	while (s[i])
	{
		j = 0;
		while (j < ft_strlen(s[i]))
		{
			if (s[i][j] == '1')
				s[i][j] = (rand() % 4) + 1 + '0';
			if (s[i][j] == 'N' || s[i][j] == 'E' || s[i][j] == 'S'
				|| s[i][j] == 'W')
				s[i][j] = '0';
			j++;
		}
		i++;
	}
	return (s);
}
