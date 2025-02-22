/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:05:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/22 16:07:34 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*init_textures(void)
{
	t_img	*result;

	result = safe_malloc(sizeof(t_img) * 4); //4 pour Nord, Sud, Est Ouest p-e + apres

	// ...

	return (result);
}


void	load_textures(t_mlx *data)
{
	int	height;
	int	width;

	data->textures[0].img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/redbrick.xpm",
		&width, &height);

	data->textures[0].height = height;
	data->textures[0].width = width;
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img_ptr,
		&data->textures[0].bpp, &data->textures[0].line_length, &data->textures[0].endian);

	data->textures[1].img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/bluestone.xpm",
		&width, &height);
	data->textures[1].height = height;
	data->textures[1].width = width;
	data->textures[1].addr = mlx_get_data_addr(data->textures[1].img_ptr,
		&data->textures[1].bpp, &data->textures[1].line_length, &data->textures[1].endian);

	data->textures[2].img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/purplestone.xpm",
		&width, &height);
	data->textures[2].height = height;
	data->textures[2].width = width;
	data->textures[2].addr = mlx_get_data_addr(data->textures[2].img_ptr,
		&data->textures[2].bpp, &data->textures[2].line_length, &data->textures[2].endian);
}

int get_texture_pixel(t_img *texture, int x, int y)
{
    char	*pixel;

	pixel = texture->addr + (y * texture->line_length) + (x * (texture->bpp / 8));
    return *(int *)pixel;
}
