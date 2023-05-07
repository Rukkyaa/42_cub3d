/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:57:09 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/07 14:45:08 by rukkyaa          ###   ########.fr       */
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
	return (c == ' ' || c == ',' || (c >= '0'
			&& c <= '9') || c == '\0' || c == '\n');
}

bool	fill_color(t_parsing *parsing, int color_index, char *line, char c)
{
	int	color;

	color = ft_atoi(line);
	if (color > 255 || (color == 0 && line[0] != '0') || len_num(line) > 3)
		return (false);
	if (c == 'F')
		parsing->floor_color[color_index] = color;
	else if (c == 'C')
		parsing->ceiling_color[color_index] = color;
	return (true);
}

bool	get_color(t_parsing *parsing, char c, char *line)
{
	int		i;
	int		color_index;
	int		color;

	i = 0;
	color_index = 0;
	while (line[++i] != '\0' && line[i] != '\n')
	{
		if (!is_valid_color_content(line[i]) || color_index > 2
			&& line[i] >= '0' && line[i] <= '9')
			return (false);
		if (line[i] >= '0' && line[i] <= '9')
		{
			if (!fill_color(parsing, color_index++, line + i, c))
				return (false);
			i += len_num(line + i);
		}
	}
	return (color_index == 3);
}

bool	get_params(t_parsing *parsing, int fd)
{
	char	*line;
	int		found;

	found = 0;
	line = "coucou";
	while (line && found < 2)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		if (line[0] == 'F')
		{
			if (!get_color(parsing, 'F', line))
				return (free(line), false);
		}
		else if (line[0] == 'C')
		{
			if (!get_color(parsing, 'C', line))
				return (free(line), false);
		}
		if (line[0] == 'F' || line[0] == 'C')
			found ++;
		free(line);
	}
	return (true);
}
