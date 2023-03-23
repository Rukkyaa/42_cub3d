/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:23:38 by teliet            #+#    #+#             */
/*   Updated: 2023/03/23 11:19:46 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

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
		if (entry->d_name[0] == '.')
			continue;
		// if (stat(ft_strjoin(dir_path, entry->d_name), &file_stat) < 0)
		// 	continue;
		// if (S_ISREG(file_stat.st_mode) && !ft_strncmp(get_filename_ext(entry->d_name), ".xpm", ft_strlen(".xpm")))
			count++;
	}
	printf("%ld\n", count);
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
		if (entry->d_name[0] == '.')
			continue;
		printf("%s\n",entry->d_name);
		imgs[i] = malloc( sizeof(t_img ));
		if (!imgs[i])
		{
			while (i > 0)
				mlx_destroy_image(game->mlx, imgs[--i]);
			free(imgs);
			closedir(dir);
			return (NULL);
		}
		ft_xpm_to_img(game, imgs[i], ft_strjoin(dir_path, ft_strjoin("/", entry->d_name))); // ft_strjoin(dir_path, entry->d_name)
		imgs[i]->name = entry->d_name;
		i++;
	}
	imgs[count] = NULL;
	sort_imgs(imgs);
	closedir(dir);
	return (imgs);
}
