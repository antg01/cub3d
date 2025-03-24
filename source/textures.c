/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:05:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/24 15:51:04 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*init_textures(void)
{
	t_img	*result;

	result = safe_malloc(sizeof(t_img) * 4);
	return (result);
}

void	load_textures(t_mlx *data)
{
	int	height;
	int	width;

	data->textures[0].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/redbrick.xpm", &width, &height);
	data->textures[0].height = height;
	data->textures[0].width = width;
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img_ptr,
			&data->textures[0].bpp, &data->textures[0].line_length,
			&data->textures[0].endian);
	data->textures[1].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/bluestone.xpm", &width, &height);
	data->textures[1].height = height;
	data->textures[1].width = width;
	data->textures[1].addr = mlx_get_data_addr(data->textures[1].img_ptr,
			&data->textures[1].bpp, &data->textures[1].line_length,
			&data->textures[1].endian);
	data->textures[2].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/eagle.xpm", &width, &height);
	data->textures[2].height = height;
	data->textures[2].width = width;
	data->textures[2].addr = mlx_get_data_addr(data->textures[2].img_ptr,
			&data->textures[2].bpp, &data->textures[2].line_length,
			&data->textures[2].endian);
	data->textures[3].img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/greystone.xpm", &width, &height);
	data->textures[3].height = height;
	data->textures[3].width = width;
	data->textures[3].addr = mlx_get_data_addr(data->textures[3].img_ptr,
			&data->textures[3].bpp, &data->textures[3].line_length,
			&data->textures[3].endian);
}

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

void	load_handgun(t_mlx *data)
{
	int	width;
	int	height;

	data->hand->img_ptr = mlx_xpm_file_to_image(data->mlx,
			"textures/handgun.xpm", &width, &height);
	if (!data->hand->img_ptr)
	{
		perror("Failed to load gun sprite");
		exit(1);
	}
	data->hand->width = width;
	data->hand->height = height;
	data->hand->addr = mlx_get_data_addr(data->hand->img_ptr,
			&data->hand->bpp, &data->hand->line_length,
			&data->hand->endian);
}
