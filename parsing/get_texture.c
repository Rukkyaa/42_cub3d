/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:03:50 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/05/07 16:01:46 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_texture(char *line)
{
	if (ft_strlen(line) < 2)
		return (false);
	if (line[0] == 'N' && line[1] == 'O')
		return (true);
	if (line[0] == 'S' && line[1] == 'O')
		return (true);
	if (line[0] == 'W' && line[1] == 'E')
		return (true);
	if (line[0] == 'E' && line[1] == 'A')
		return (true);
	return (false);
}

bool	fill_texture(t_parsing *parsing, char *line)
{
	int		start;
	int		end;
	char	*texture;

	start = 1;
	while (line[++start] && line[start] == ' ')
		;
	end = start;
	while (line[end] && line[end] != ' ' && line[end] != '\n')
		end++;
	texture = ft_substr(line, start, end - start);
	if (!texture)
		return (false);
	if (line[0] == 'N' && line[1] == 'O')
		parsing->no = texture;
	if (line[0] == 'S' && line[1] == 'O')
		parsing->so = texture;
	if (line[0] == 'W' && line[1] == 'E')
		parsing->we = texture;
	if (line[0] == 'E' && line[1] == 'A')
		parsing->ea = texture;
	return (true);
}