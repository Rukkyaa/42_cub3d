/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_animation_sprites.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:23:38 by teliet            #+#    #+#             */
/*   Updated: 2023/03/09 19:33:56 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
/*
** Load an XPM image file from the given path using the game's mlx instance.
** Returns a pointer to the resulting t_img struct, or NULL on error.
*/
// static t_img	*ft_xpm_to_img_wrapper(t_game *game, char *path)
// {
// 	t_img	*img;

// 	img = (t_img *)malloc(sizeof(t_img));
// 	if (!img)
// 		return (NULL);
// 	img->ptr = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
// 	if (!img->ptr)
// 	{
// 		free(img);
// 		return (NULL);
// 	}
// 	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
// 	return (img);
// }

/*
** Load all XPM files in the given directory and return an array of t_img pointers.
** Returns NULL on error or if the directory is empty.
*/
t_img	**fill_sprite_animation(t_game *game, char *dir_path)
{
	DIR				*dir;
	struct dirent	*entry;
	t_img			**imgs;
	size_t			count;
	size_t			i;

	dir = opendir(dir_path);
	if (!dir)
		return (NULL);
	count = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_type == DT_REG && !ft_strchr(entry->d_name, ".xpm"))
			count++;
	}
	if (count == 0)
	{
		closedir(dir);
		return (NULL);
	}
	imgs = (t_img **)malloc((count + 1) * sizeof(t_img *));
	if (!imgs)
	{
		closedir(dir);
		return (NULL);
	}
	i = 0;
	rewinddir(dir);
	while ((entry = readdir(dir)))
	{
		if (entry->d_type == DT_REG && !ft_strchr(entry->d_name, ".xpm"))
		{
			imgs[i] = ft_xpm_to_img(game, ft_strjoin(dir_path, entry->d_name));
			if (!imgs[i])
			{
				while (i > 0)
					mlx_destroy_image(game->mlx, imgs[--i]);
				free(imgs);
				closedir(dir);
				return (NULL);
			}
			i++;
		}
	}
	imgs[count] = NULL;
	closedir(dir);
	return (imgs);
}
