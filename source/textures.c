/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:25:21 by gnyssens          #+#    #+#             */
/*   Updated: 2025/04/01 17:29:26 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Charge deux textures par défaut (redbrick et bluestone)
** dans la structure texture.
*/
void	load_text1(t_mlx *data, int *height, int *width)
{
	data->textures[0].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/redbrick.xpm", width, height);
	if (!(data->textures[0].img_ptr))
		my_exit("texture loading failed !\n", data);
	data->textures[0].height = *height;
	data->textures[0].width = *width;
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img_ptr,
			&data->textures[0].bpp, &data->textures[0].line_length,
			&data->textures[0].endian);
	data->textures[1].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/bluestone.xpm", width, height);
	if (!(data->textures[1].img_ptr))
		my_exit("texture loading failed !\n", data);
	data->textures[1].height = *height;
	data->textures[1].width = *width;
	data->textures[1].addr = mlx_get_data_addr(data->textures[1].img_ptr,
			&data->textures[1].bpp, &data->textures[1].line_length,
			&data->textures[1].endian);
}

/*
** Charge deux autres textures par défaut (eagle et greystone)
** dans la structure texture.
*/
void	load_text2(t_mlx *data, int *height, int *width)
{
	data->textures[2].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/eagle.xpm", width, height);
	if (!(data->textures[2].img_ptr))
		my_exit("texture loading failed !\n", data);
	data->textures[2].height = *height;
	data->textures[2].width = *width;
	data->textures[2].addr = mlx_get_data_addr(data->textures[2].img_ptr,
			&data->textures[2].bpp, &data->textures[2].line_length,
			&data->textures[2].endian);
	data->textures[3].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/greystone.xpm", width, height);
	if (!(data->textures[3].img_ptr))
		my_exit("texture loading failed !\n", data);
	data->textures[3].height = *height;
	data->textures[3].width = *width;
	data->textures[3].addr = mlx_get_data_addr(data->textures[3].img_ptr,
			&data->textures[3].bpp, &data->textures[3].line_length,
			&data->textures[3].endian);
}

/*
** Charge l'ensemble des textures par défaut en
** appelant les fonctions de chargement.
*/
void	load_textures(t_mlx *data)
{
	int	height;
	int	width;

	load_text1(data, &height, &width);
	load_text2(data, &height, &width);
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
