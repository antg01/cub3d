/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:07:54 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/24 15:46:52 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	which_row(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if ('N' == map[i][j] || 'S' == map[i][j] || 'E' == map[i][j]
				|| 'W' == map[i][j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	which_col(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if ('N' == row[i] || 'S' == row[i] || 'E' == row[i] || 'W' == row[i])
			return (i);
		i++;
	}
	return (-1);
}

void	set_start_dirs(t_mlx *data, t_player *player)
{
	if (*(data->orientation) == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (*(data->orientation) == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (*(data->orientation) == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (*(data->orientation) == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

t_player	*init_player(t_mlx *data)
{
	t_player	*player;
	int			coord_player[2];

	player = (t_player *)safe_malloc(sizeof(t_player));
	coord_player[0] = which_row(data->map);
	coord_player[1] = which_col(data->map[coord_player[0]]);
	player->x_pos = (double)(coord_player[1] + 0.50);
	player->y_pos = (double)(coord_player[0] + 0.50);
	set_start_dirs(data, player);
	player->rot_speed = PI / 16;
	player->plane_x = -player->dir_y * tan(0.576);
	player->plane_y = player->dir_x * tan(0.576);
	player->camera_x = -1;
	player->ray_dir_x = player->dir_x + player->plane_x * player->camera_x;
	player->ray_dir_y = player->dir_y + player->plane_y * player->camera_x;
	return (player);
}

int	check_wall(t_mlx *data, int x, int y)
{
	int	old_x;
	int	old_y;
	int	dx;
	int	dy;
	int	xy[2];

	if (x < 0 || y < 0 || x > data->longest_row || y > data->num_rows)
		return (0);
	if (data->map[y][x] == '1')
		return (0);
	old_x = (int)data->player->x_pos;
	old_y = (int)data->player->y_pos;
	set_dir_x_y(data, &dx, &dy);
	set_xy(xy, x, y);
	if (old_x + dx != x && old_y + dy != y)
	{
		dx *= (-1);
		dy *= (-1);
	}
	if (old_x != x && old_y != y)
	{
		if (!(norm_fix(data, dx, dy, xy)))
			return (0);
	}
	return (1);
}
