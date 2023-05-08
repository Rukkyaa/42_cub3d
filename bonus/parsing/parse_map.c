/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:43:09 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/08 17:34:42 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_valid_content(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	check_map_content(t_parsing *parsing, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_valid_content(map[i][j]))
				return (false);
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (parsing->player_pos.x != 0 || parsing->player_pos.y != 0)
					return (false);
				parsing->player_pos = (t_vector){j, i};
				parsing->player_dir = map[i][j];
			}
		}
	}
	return (parsing->player_dir != 0);
}

bool	check_voisin(t_parsing *parsing, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || i == parsing->map_height - 1 || j == 0
					|| !map[i][j + 1] || map[i][j + 1] == '\n')
					return (false);
				if ((int)ft_strlen(map[i + 1]) - 1 < j
					|| (int)ft_strlen(map[i - 1]) - 1 < j)
					return (false);
				if (map[i + 1][j] == ' ' || map[i - 1][j] == ' '
					|| map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
					return (false);
			}
		}
	}
	return (true);
}

/*
** @brief: Function to check if the map is valid
** @param map: The map to check
** @return: True if the map is valid, False otherwise
*/
bool	is_map_valid(t_parsing *parsing)
{
	char	**map;
	bool	ret;

	map = map_dup(parsing->map);
	if (!map)
		return (false);
	parsing->map_height = map_height(map);
	parsing->map_width = map_width(map);
	parsing->player_pos = (t_vector){0, 0};
	parsing->player_dir = 0;
	if (!check_map_content(parsing, map))
	{
		free_map(map);
		return (false);
	}
	ret = check_voisin(parsing, map);
	free_map(map);
	return (ret);
}
