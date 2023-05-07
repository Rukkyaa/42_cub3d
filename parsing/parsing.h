/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:48:49 by axlamber          #+#    #+#             */
/*   Updated: 2023/05/07 15:49:03 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

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
	t_vector	player_pos;
	int			floor_color[3];
	int			ceiling_color[3];
	int			map_width;
	int			map_height;
	char		player_dir;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_parsing;

int			ft_strlen(char const *str);
int			map_height(char **map);
int			map_width(char **map);
char		**get_map(int fd);
t_parsing	*parse(char	*map_path);
void		free_map(char **map);
char		**map_dup(char **map);
bool		is_map_valid(t_parsing *parsing);
int			ft_atoi(const char *str);
int			len_num(const char *line);

bool		get_params(t_parsing *parsing, int fd);
bool		get_color(t_parsing *parsing, char *line);
bool		is_texture(char *line);
bool		fill_texture(t_parsing *parsing, char *line);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// GNL
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*get_next_line(int fd);

#endif