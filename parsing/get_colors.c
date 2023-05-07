/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:57:09 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/07 13:32:14 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	len_num(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		++i;
	return (i);
}

bool	is_valid_color_content(char c)
{
	return (c == ' ' || c == ',' || (c >= '0' && c <= '9') || c == '\0' || c == '\n');
}

bool	get_color(t_parsing *parsing, char c, char *line)
{
	int		i;
	int		color_index;

	i = 1;
	color_index = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (!is_valid_color_content(line[i]))
		{
			free(line);
			return (false);
		}
		if (color_index > 2 && line[i] >= '0' && line[i] <= '9')
		{
			free(line);
			return (false);
		}
		if (line[i] >= '0' && line[i] <= '9')
		{
			if (c == 'F')
			{
				parsing->floor_color[color_index] = ft_atoi(line + i);
				if (parsing->floor_color[color_index] > 255 || (parsing->floor_color[color_index] == 0 && line[i] != '0') || len_num(line + i) > 3)
				{
					free(line);
					return (false);
				}
				i += len_num(line + i);
			}
			else if (c == 'C')
			{
				parsing->ceiling_color[color_index] = ft_atoi(line + i);
				if (parsing->ceiling_color[color_index] > 255 || (parsing->ceiling_color[color_index] == 0 && line[i] != '0') || len_num(line + i) > 3)
				{
					free(line);
					return (false);
				}
				i += len_num(line + i);
			}
			++color_index;
		}
		++i;
	}
	return (true);
}

bool	get_params(t_parsing *parsing, int fd)
{
	char	*line;
	int		found;

	found = 0;
	line = "coucou";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		if (line[0] == 'F')
		{
			if (!get_color(parsing, 'F', line))
				return (false);
			found++;
		}
		else if (line[0] == 'C')
		{
			if (!get_color(parsing, 'C', line))
				return (false);
			found++;
		}
		free(line);
		if (found == 2)
			break ;
	}
	return (true);
}