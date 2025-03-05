/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top-down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:34:59 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 15:50:21 by gnyssens         ###   ########.fr       */
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
	int	cell_size;
	int	x;
	int	y;
	int	y_limit;
	int	x_limit;
	int	biggest_line;

	if (data->longest_row > num_rows)
		biggest_line = data->longest_row;
	else
		biggest_line = num_rows;
	cell_size = IMAGE_HEIGHT / biggest_line;
	y = WINDOW_HEIGHT - num_rows * cell_size;
	y_limit = y + (num_rows - 1) * cell_size;
	x_limit = data->longest_row * cell_size;
	while (y <= y_limit)
	{
		x = 0;
		while (x < x_limit)
		{
			//if (x == 0 || x >= (num_rows - 1) * cell_size
			//	|| y ==  WINDOW_HEIGHT - (num_rows * cell_size) || y == y_limit)
			//	draw_square(data, x, y, cell_size, RED);
			if (!data->map[(y - WINDOW_HEIGHT + (num_rows * cell_size)) / cell_size][(x / cell_size)])
				break ;
			else if (data->map[(y - WINDOW_HEIGHT + (num_rows * cell_size)) / cell_size][(x / cell_size)] == '1')
				draw_square(data, x, y, cell_size, DARK_RED);
			else
				draw_square(data, x, y, cell_size, 0xFFFFFF);
			x += cell_size;
		}
		y += cell_size;
	}
}

void	draw_player(t_mlx *data)
{
	int i_start;
	int	j_start;
	int	i;
	int	j;
	int	cellsize;
	int	biggest_line;

	if (data->longest_row > data->num_rows)
		biggest_line = data->longest_row;
	else
		biggest_line = data->num_rows;

	cellsize = IMAGE_HEIGHT / biggest_line;
	i_start = (data->player->y_pos * cellsize + WINDOW_HEIGHT - (data->num_rows * cellsize)) - 2;
	i = i_start;
	while (i < i_start + 4)
	{
		j_start = (data->player->x_pos * cellsize) - 2;
		j = j_start;
		while (j < j_start + 4)
		{
			my_mlx_pixel_put(data, j, i, DARK_BLUE);
			j++;
		}
		i++;
	}
}

//ca cest la fonction qui cree la minimap
int	render(t_mlx *data)
{
    draw_grid(data, data->num_rows);
	draw_player(data);
	draw_rays(data, data->player);
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);

	return (0);
}
