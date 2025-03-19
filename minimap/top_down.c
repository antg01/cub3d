/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:34:59 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 19:04:54 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_white_square(t_mlx *data, int x_start, int y_start, int size)
{
	int	i;
	int	j;
	int	color;

	color = 0xFFFFFF;
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

void	draw_red_square(t_mlx *data, int x_start, int y_start, int size)
{
	int	i;
	int	j;
	int	color;

	color = DARK_RED;
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

void	draw_grid(t_mlx *data, int num_rows, int cell_size)
{
	t_grid	g;

	set_biggest_line(data, &g, num_rows);
	cell_size = IMAGE_HEIGHT / g.biggest_line;
	g.y = WINDOW_HEIGHT - num_rows * cell_size;
	g.y_limit = g.y + (num_rows - 1) * cell_size;
	g.x_limit = data->longest_row * cell_size;
	while (g.y <= g.y_limit)
	{
		g.x = 0;
		while (g.x < g.x_limit)
		{
			if (!data->map[(g.y - WINDOW_HEIGHT + (num_rows * cell_size))
					/ cell_size][(g.x / cell_size)])
				break ;
			else if (data->map[(g.y - WINDOW_HEIGHT + (num_rows * cell_size))
					/ cell_size][(g.x / cell_size)] == '1')
				draw_red_square(data, g.x, g.y, cell_size);
			else
				draw_white_square(data, g.x, g.y, cell_size);
			g.x += cell_size;
		}
		g.y += cell_size;
	}
}

void	draw_player(t_mlx *data, int i)
{
	int	i_start;
	int	j_start;
	int	j;
	int	cellsize;
	int	biggest_line;

	if (data->longest_row > data->num_rows)
		biggest_line = data->longest_row;
	else
		biggest_line = data->num_rows;
	cellsize = IMAGE_HEIGHT / biggest_line;
	i_start = (data->player->y_pos * cellsize
			+ WINDOW_HEIGHT - (data->num_rows * cellsize)) - 2;
	i = i_start - 1;
	while (++i < i_start + 4)
	{
		j_start = (data->player->x_pos * cellsize) - 2;
		j = j_start;
		while (j < j_start + 4)
		{
			my_mlx_pixel_put(data, j, i, DARK_BLUE);
			j++;
		}
	}
}

int	render(t_mlx *data)
{
	draw_grid(data, data->num_rows, 0);
	draw_player(data, 0);
	draw_rays(data, data->player);
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	return (0);
}
