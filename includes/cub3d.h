/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:45:39 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/16 17:21:42 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx/mlx.h"
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define ESC 65307
# define A 97
# define W 119
# define D 100
# define S 115

// COLORS
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define BLACK_PIXEL 0x000000

typedef struct s_player
{
	int		x;
	int		y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_player	player;
}				t_game;

void	var_init(t_game *game);
char	**get_map(char *arg);
int		key_gestion(int keycode, t_game *game);
int		close_window(t_game *game);
void	move(t_game *game, char direction);
void	draw_square(t_game *game, int x, int y, int width, int color);

#endif
