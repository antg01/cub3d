/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:05:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/20 19:21:01 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/*
t_img	*init_textures(void)
{
	t_img	*result;

	result = safe_malloc(sizeof(t_img) * 4); //4 pour Nord, Sud, Est Ouest p-e + apres

	// ...

	return (result);
}
*/

void	load_textures(t_mlx *data)
{
	int	height;
	int	width;

	data->textures[0].img_ptr = mlx_xpm_file_to_image(data->mlx, "../textures/redbrick.xpm",
		&width, &height);
	data->textures[0].height = height;
	data->textures[0].width = width;
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img_ptr,
		&data->textures[0].bpp, &data->textures[0].line_length, &data->textures[0].endian);
}
