/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:48:49 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 12:59:09 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_parsing
{
	char		**map;
	int			map_width;
	int			map_height;
	t_vector	player_pos;
	char		player_dir;
}				t_parsing;

int			ft_strlen(char const *str);
int			map_height(char **map);
int			map_width(char **map);
char		**get_map(char *map_path);
t_parsing	*parse(char	*map_path);
void		free_map(char **map);
char		**map_dup(char **map);
bool		is_map_valid(t_parsing *parsing);


// GNL
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*get_next_line(int fd);

#endif