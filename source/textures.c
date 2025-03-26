/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:25:21 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/26 17:05:21 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Charge deux textures par défaut (redbrick et bluestone)
** dans la structure texture.
*/
void	load_text1(t_mlx *data, int *height, int *width, int i)
{
	data->textures[i].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/redbrick.xpm", width, height);
	data->textures[i].height = *height;
	data->textures[i].width = *width;
	data->textures[i].addr = mlx_get_data_addr(data->textures[i].img_ptr,
			&data->textures[i].bpp, &data->textures[i].line_length,
			&data->textures[i].endian);
	data->textures[i].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/bluestone.xpm", width, height);
	data->textures[i].height = *height;
	data->textures[i].width = *width;
	data->textures[i].addr = mlx_get_data_addr(data->textures[i].img_ptr,
			&data->textures[i].bpp, &data->textures[i].line_length,
			&data->textures[i].endian);
}

/*
** Charge deux autres textures par défaut (eagle et greystone)
** dans la structure texture.
*/
void	load_text2(t_mlx *data, int *height, int *width, int i)
{
	data->textures[i].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/eagle.xpm", width, height);
	data->textures[i].height = *height;
	data->textures[i].width = *width;
	data->textures[i].addr = mlx_get_data_addr(data->textures[i].img_ptr,
			&data->textures[i].bpp, &data->textures[i].line_length,
			&data->textures[i].endian);
	data->textures[i].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/greystone.xpm", width, height);
	data->textures[i].height = *height;
	data->textures[i].width = *width;
	data->textures[i].addr = mlx_get_data_addr(data->textures[i].img_ptr,
			&data->textures[i].bpp, &data->textures[i].line_length,
			&data->textures[i].endian);
}

/*
** Charge l'ensemble des textures par défaut en
** appelant les fonctions de chargement.
*/
void	load_textures(t_mlx *data)
{
	int	height;
	int	width;
	int	i;

	i = 0;
	while (i < 2)
	{
		load_text1(data, &height, &width, i);
		i++;
	}
	while (i < 4)
	{
		load_text2(data, &height, &width, i);
		i++;
	}
}

/*
** Récupère la couleur d’un pixel dans une texture en vérifiant les coordonnées.
*/
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (!texture || x < 0 || y < 0 || x >= texture->width
		|| y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length) + (x * (texture->bpp
				/ 8));
	return (*(int *)pixel);
}

