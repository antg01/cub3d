/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:07:54 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/03 15:50:43 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//in which row is 'N' (player)
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
			if ('N' == map[i][j])
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
		if ('N' == row[i])
			return (i);
		i++;
	}
	return (-1);
}

//incomplet, pr l'instant juste pos pr top-down
t_player	*init_player(t_mlx *data)
{
	t_player	*player;
	int			coord_player[2]; //[y][x]

	player = (t_player *)safe_malloc(sizeof(t_player));
	coord_player[0] = which_row(data->map);
	coord_player[1] = which_col(data->map[coord_player[0]]);
	player->x_pos = (double) (coord_player[1] + 0.50); //jsp si cst bien, pr qu'il soit 'au milieu'
	player->y_pos = (double) (coord_player[0] + 0.50);
	player->dir_x = 0; //vers le Nord pr commencer
	player->dir_y = -1;
	player->rot_speed = PI / 16;

	//ci-dessous ça sera p-e trasnféré vers t_raycast (struct)
	player->plane_x = -player->dir_y * tan(0.576); //0.576rad == 33°
	player->plane_y = player->dir_x * tan(0.576);
	player->camera_x =  -1; //cv de -1 à 1
	player->ray_dir_x = player->dir_x + player->plane_x * player->camera_x;
	player->ray_dir_y = player->dir_y + player->plane_y * player->camera_x;

	return (player);
}

int	check_wall(t_mlx *data, int x, int y)
{
	int			old_x;
	int			old_y;
	int			dx; //dir_x
	int			dy; //dir_y

	if (x < 0 || y < 0 || x > data->num_rows || y > data->num_rows)
		return (0);
	if (data->map[y][x] == '1')
		return (0);
	old_x = data->player->x_pos;
	old_y = data->player->y_pos;
	if (data->player->dir_x > 0)
		dx = 1;
	else if (data->player->dir_x == 0)
		dx = 0;
	else
		dx = -1;
	if (data->player->dir_y > 0)
		dy = 1;
	else if (data->player->dir_y == 0)
		dy = 0;
	else
		dy = -1;
	if (old_x != x && old_y != y) //ca veut dire que ya changement diagonal (de 2 cases)
	{
		if (dx == 1 && dy == 1)
		{
			if (data->map[y - 1][x] == '1' && data->map[y][x - 1] == '1')
				return (0);
		}
		else if (dx == 1 && dy == -1)
		{
			if (data->map[y + 1][x] == '1' && data->map[y][x - 1] == '1')
				return (0);
		}
		else if (dx == -1 && dy == 1)
		{
			if (data->map[y - 1][x] == '1' && data->map[y][x + 1] == '1')
				return (0);
		}
		else if (dx == -1 && dy == -1)
		{
			if (data->map[y + 1][x] == '1' && data->map[y][x + 1] == '1')
				return (0);
		}
	}
	return (1);
}
