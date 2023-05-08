/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:57:09 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/08 18:24:26 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	get_map_color(t_parsing *parsing, char *line)
{
	int		i;
	int		color_index;
	char	c;

	c = line[0];
	i = 0;
	color_index = 0;
	while (line[++i] != '\0' && line[i] != '\n')
	{
		if (!is_valid_color_content(line[i]) || (color_index > 2
				&& line[i] >= '0' && line[i] <= '9'))
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
