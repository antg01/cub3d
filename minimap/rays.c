/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:03:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/24 14:56:06 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rays_check_wall(t_mlx *data, int x, int y)
{
	int	old_x;
	int	old_y;
	int	dx;
	int	dy;
	int	xy[2];

	if (!data || !data->map || y < 0 || x < 0
		|| x >= data->longest_row || y >= data->num_rows
		|| !data->map[y] || data->map[y][x] == '1')
		return (0);
	old_x = (int)data->player->x_pos;
	old_y = (int)data->player->y_pos;
	set_dir_x_y(data, &dx, &dy);
	xy[0] = x;
	xy[1] = y;
	if (old_x != x && old_y != y)
	{
		if (!(norm_fix(data, dx, dy, xy)))
			return (0);
	}
	return (1);
}

void	draw_long_line(t_mlx *data, double x, double y, double *dir_xy)
{
	int		cellsize;
	double	img_x;
	double	img_y;
	int		i;
	int		biggest_line;

	if (data->longest_row > data->num_rows)
		biggest_line = data->longest_row;
	else
		biggest_line = data->num_rows;
	cellsize = IMAGE_HEIGHT / biggest_line;
	img_x = (x * cellsize) + 4 * dir_xy[0];
	img_y = ((y * cellsize) + WINDOW_HEIGHT
			- (data->num_rows * cellsize)) + 4 * dir_xy[1];
	i = -1;
	while (1)
	{
		if (!rays_check_wall(data, (img_x / cellsize), (img_y - WINDOW_HEIGHT
					+ (data->num_rows * cellsize)) / cellsize))
			break ;
		if (++i == 0 || i % cellsize == 0)
			my_mlx_pixel_put(data, (int) img_x, (int) img_y, BLUE);
		img_x += dir_xy[0] * 1.0;
		img_y += dir_xy[1] * 1.0;
	}
}

void	draw_rays(t_mlx *data, t_player *player)
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		i;
	float	save_dir_x;
	double	dir_xy[2];

	ray_dir_x = player->dir_x * cos(-0.185 * PI)
		- player->dir_y * sin(-0.185 * PI);
	ray_dir_y = player->dir_x * sin(-0.185 * PI)
		+ player->dir_y * cos(-0.185 * PI);
	i = 0;
	while (i < 400)
	{
		dir_xy[0] = ray_dir_x;
		dir_xy[1] = ray_dir_y;
		draw_long_line(data, player->x_pos,
			player->y_pos, dir_xy);
		i++;
		save_dir_x = ray_dir_x;
		ray_dir_x = ray_dir_x * cos(0.000925 * PI)
			- ray_dir_y * sin(0.000925 * PI);
		ray_dir_y = save_dir_x * sin(0.000925 * PI)
			+ ray_dir_y * cos(0.000925 * PI);
	}
}
