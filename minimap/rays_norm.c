/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:56:13 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/24 15:46:08 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_dir_x_y(t_mlx *data, int *dx, int *dy)
{
	if (data->player->dir_x > 0)
		*dx = 1;
	else if (data->player->dir_x < 0)
		*dx = -1;
	else
		*dx = 0;
	if (data->player->dir_y > 0)
		*dy = 1;
	else if (data->player->dir_y < 0)
		*dy = -1;
	else
		*dy = 0;
}

int	norm_fix(t_mlx *data, int dx, int dy, int *xy)
{
	if ((dx == 1 && dy == 1 && xy[1] > 0 && xy[0] > 0)
		&& data->map[xy[1] - 1] && data->map[xy[1] - 1][xy[0]] ==
			'1' && data->map[xy[1]][xy[0] - 1] == '1')
		return (0);
	else if (dx == 1 && dy == -1 && xy[1] + 1 < data->num_rows && xy[0] > 0)
	{
		if (data->map[xy[1] + 1] && data->map[xy[1] + 1][xy[0]] ==
			'1' && data->map[xy[1]][xy[0] - 1] == '1')
			return (0);
	}
	else if (dx == -1 && dy == 1 && xy[1] > 0 && xy[0] + 1 < data->longest_row)
	{
		if (data->map[xy[1] - 1] && data->map[xy[1] - 1][xy[0]] ==
			'1' && data->map[xy[1]][xy[0] + 1] == '1')
			return (0);
	}
	else if (dx == -1 && dy == -1 && xy[1] + 1 < data->num_rows
		&& xy[0] + 1 < data->longest_row)
	{
		if (data->map[xy[1] + 1] && data->map[xy[1] + 1][xy[0]] ==
			'1' && data->map[xy[1]][xy[0] + 1] == '1')
			return (0);
	}
	return (1);
}

void	set_xy(int *xy, int x, int y)
{
	xy[0] = x;
	xy[1] = y;
}
