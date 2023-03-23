/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:16:26 by axlamber          #+#    #+#             */
/*   Updated: 2023/03/23 22:02:50 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char			*strjoin;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	strjoin = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!strjoin)
		return (NULL);
	while (s1[i])
	{
		strjoin[i] = s1[i];
		i ++;
	}
	while (s2[j])
	{
		strjoin[j + i] = s2[j];
		j ++;
	}
	strjoin[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (strjoin);
}

static char *random_wall(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = -1;
	srand(time(NULL));
	while (++i < len)
		if (s[i] == '1')
			s[i] = (rand() % 4) + 1 + '0';
	return s;
}

static char	**string_to_map(char *s)
{
	char	**array;

	if (!s)
		return (NULL);
	s = random_wall(s);
	array = ft_split(s, '\n');
	free(s);
	if (!array)
		return (NULL);
	return (array);
}

static char	**fd_to_map(int fd)
{
	ssize_t	len_read;
	char	*str;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	str = (char *)malloc(1 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	len_read = 1;
	while (len_read)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		if (len_read == -1)
		{
			free(str);
			return (NULL);
		}
		buffer[len_read] = '\0';
		str = ft_strjoin_free(str, buffer);
	}
	free(buffer);
	return (string_to_map(str));
}

char	**get_map(char *arg)
{
	int		fd;
	char	**map;

	fd = open(arg, O_RDONLY);
	if (fd < 0 || fd > 1024)
		return (NULL);
	map = fd_to_map(fd);
	if (!map)
		return (NULL);
	return (map);
}
