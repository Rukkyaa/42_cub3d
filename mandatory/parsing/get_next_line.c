/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:24 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 18:24:31 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*before(char *buffer)
{
	char			*split;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!(*buffer))
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i ++;
	if (buffer[i] == '\n')
		i ++;
	split = malloc((i + 1) * sizeof(char));
	if (!split)
		return (NULL);
	while (j < i)
	{
		split[j] = buffer[j];
		j ++;
	}
	split[j] = '\0';
	return (split);
}

static char	*after(char *buffer)
{
	char			*split;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i ++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i ++;
	split = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!split)
		return (NULL);
	while (buffer[i])
		split[j++] = buffer[i++];
	split[j] = '\0';
	free(buffer);
	return (split);
}

char	*get_line(int fd, char *save)
{
	char	*buffer;
	int		readed;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	readed = 1;
	while (!ft_strchr(save, '\n') && readed != 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readed] = '\0';
		if (!save)
			save = ft_strdup(buffer);
		else
			save = ft_strjoin_free(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_line(fd, save);
	if (!save)
		return (NULL);
	line = before(save);
	save = after(save);
	return (line);
}
