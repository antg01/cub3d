/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_down_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:55:19 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/26 13:56:16 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	draw_white(t_mlx *data, t_grid *g, int cell_size, int num_rows)
{
	if (data->map[(g->y - WINDOW_HEIGHT + (num_rows * cell_size))
			/ cell_size][(g->x / cell_size)] == '0'
			|| data->map[(g->y - WINDOW_HEIGHT + (num_rows * cell_size))
			/ cell_size][(g->x / cell_size)] == 'N'
					|| data->map[(g->y - WINDOW_HEIGHT + (num_rows * cell_size))
			/ cell_size][(g->x / cell_size)] == 'S'
					|| data->map[(g->y - WINDOW_HEIGHT + (num_rows * cell_size))
			/ cell_size][(g->x / cell_size)] == 'E'
					|| data->map[(g->y - WINDOW_HEIGHT + (num_rows * cell_size))
			/ cell_size][(g->x / cell_size)] == 'W')
		return (1);
	else
		return (0);
}

void	set_biggest_line(t_mlx *data, t_grid *g, int num_rows)
{
	if (data->longest_row > num_rows)
		g->biggest_line = data->longest_row;
	else
		g->biggest_line = num_rows;
}
