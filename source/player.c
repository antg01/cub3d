/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:07:54 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/05 22:21:55 by gnyssens         ###   ########.fr       */
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
	int			cell_size;
	int			coord_player[2]; //[y][x]

	cell_size = IMAGE_HEIGHT / data->num_rows;
	player = (t_player *)safe_malloc(sizeof(t_player));
	coord_player[0] = which_row(data->map);
	coord_player[1] = which_col(data->map[coord_player[0]]);
	player->x_pos = (3 + 0.5 + coord_player[1]) * cell_size; //3 pr décalage, 0.5 pr etre au milieu carré
	player->y_pos = (1 + 0.5 + coord_player[0]) * cell_size;
	player->dir_x = 0; //vers le Nord pr commencer
	player->dir_y = -1;
	player->rot_speed = PI / 8; //choisi un peu à la one
	return (player);
}

int	check_wall(t_mlx *data, float x, float y)
{
	char	*dest;
	int		round_x;
	int		round_y;

	round_x = round_float(x);
	round_y = round_float(y);
	dest = data->addr + (round_y * data->line_length + round_x * (data->bits_per_pixel / 8));
	if (*(unsigned int *)dest == 0xEE0000)
	{
		return (0);
	}
	return (1);
}
