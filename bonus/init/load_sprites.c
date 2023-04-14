/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:23:38 by teliet            #+#    #+#             */
/*   Updated: 2023/04/14 17:02:16 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// static const char	*get_filename_ext(const char *filename)
// {
// 	const char	*dot;

// 	dot = strrchr(filename, '.');
// 	if (!dot || dot == filename)
// 		return ("");
// 	return (dot + 1);
// }

static int	count_nb_files(char *dir_path)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;

	dir = opendir(dir_path);
	if (!dir)
		return (0);
	count = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.')
			continue ;
		count++;
	}
	closedir(dir);
	return (count);
}

/*
** Load all XPM files in the given directory and return an array of
** t_img pointers. Returns NULL on error or if the directory is empty.
*/
void	fill_sprite_animation(t_game *game, char *dir_path,
	t_animation *animation)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;
	size_t			i;
	char			*name;
	char			*tmp;

	dir = opendir(dir_path);
	if (!dir)
		return ;
	count = count_nb_files(dir_path);
	if (!count)
	{
		closedir(dir);
		return ;
	}
	animation->imgs = (t_img **)malloc((count + 1) * sizeof(t_img *));
	if (!animation->imgs)
	{
		closedir(dir);
		return ;
	}
	i = 0;
	rewinddir(dir);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.')
			continue ;
		animation->imgs[i] = malloc(sizeof(t_img));
		if (!animation->imgs[i])
		{
			while (i > 0)
				mlx_destroy_image(game->mlx, animation->imgs[--i]);
			free(animation->imgs);
			closedir(dir);
			return ;
		}
		tmp = ft_strjoin("/", entry->d_name);
		name = ft_strjoin(dir_path, tmp);
		ft_xpm_to_img(game, animation->imgs[i], name);
		free(tmp);
		free(name);
		animation->imgs[i]->name = entry->d_name;
		i++;
	}
	animation->imgs[count] = NULL;
	animation->current_img = animation->imgs[0];
	animation->nb_imgs = count;
	animation->current_frame = 0;
	animation->frame_offset = 0;
	sort_imgs(animation->imgs);
	closedir(dir);
}
