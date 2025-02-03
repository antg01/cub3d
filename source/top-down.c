/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top-down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:34:59 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/04 00:59:01 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_square(t_mlx *data, int x_start, int y_start, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j == 0 || j == size - 1 || i == 0 || i == size - 1)
				my_mlx_pixel_put(data, x_start + j, y_start + i, GRAY);
			else
				my_mlx_pixel_put(data, x_start + j, y_start + i, color);
			j++;
		}
		i++;
	}	
}

void	draw_grid(t_mlx *data, int num_rows)
{
	int	cell_size = IMAGE_HEIGHT / num_rows;
	int	x;
	int	y;

	y = 1 * cell_size;
	while (y < IMAGE_HEIGHT + (1 * cell_size))
	{
		x = 3 * cell_size;
		while (x < IMAGE_LENGTH + (3 * cell_size))
		{
			if (x == 3 * cell_size || x == IMAGE_LENGTH + (2 * cell_size)
				|| y == 1 * cell_size || y == IMAGE_HEIGHT + cell_size
				|| data->map[(y / cell_size) - 1][(x / cell_size) - 3] == '1')
				draw_square(data, x, y, cell_size, 0xEE0000);
			else
				draw_square(data, x, y, cell_size, 0xFFFFFF);
			x += cell_size;
		}
		y += cell_size;
	}
}

int	render(t_mlx *data)
{
    draw_grid(data, 10);  // 10 = NUMBER_ROWS hardcodée
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);

	return (0);
}
