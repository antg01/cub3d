/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:03:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 14:40:22 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rays_check_wall(t_mlx *data, int x, int y)
{
	int			old_x;
	int			old_y;
	int			dx; //dir_x
	int			dy; //dir_y

	if (x < 0 || y < 0 || x > data->longest_row || y > data->num_rows)
		return (0);
	if (data->map[y][x] == '1')
		return (0);
	old_x = (int)data->player->x_pos;
	old_y = (int)data->player->y_pos;
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

// chatGPT (pcq flemme)
void draw_long_line(t_mlx *data, double x, double y, double dir_x, double dir_y)
{
	int	cellsize = IMAGE_HEIGHT / data->num_rows;
	double	img_x;
	double	img_y;
	int		i;

	img_x =  (x * cellsize) + 4 * dir_x; // + 4 * dir pr pas que ca cache le player blue dot
	img_y =  ((y * cellsize) + WINDOW_HEIGHT - (data->num_rows * cellsize)) + 4 * dir_y;
	i = 0;
    while (1)
	{
		if (!rays_check_wall(data,(img_x / cellsize), (img_y - WINDOW_HEIGHT + (data->num_rows * cellsize)) / cellsize))
			break ;
		if (i == 0 || i % cellsize == 0)
        	my_mlx_pixel_put(data, (int) img_x, (int) img_y, BLUE);
        img_x += dir_x * 1.0; //retire le * cellsize stv des vrais rays
        img_y += dir_y * 1.0;
		i++;
    }
}

// FOV == 0.37 * PI
// start_dir = player_dir - 0.185 * PI vers la gauche, puis 10x rays de 0.037 * PI
void	draw_rays(t_mlx *data, t_player *player)
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		i;
	float	save_dir_x;

	ray_dir_x = player->dir_x * cos(-0.185 * PI) - player->dir_y * sin(-0.185 * PI);
	ray_dir_y = player->dir_x * sin(-0.185 * PI) + player->dir_y * cos(-0.185 * PI);
	
	i = 0;
	while (i < 400)
	{
		draw_long_line(data, player->x_pos, player->y_pos, ray_dir_x, ray_dir_y);
		i++;
		save_dir_x = ray_dir_x;
		ray_dir_x = ray_dir_x * cos(0.000925 * PI) - ray_dir_y * sin(0.000925 * PI);
		ray_dir_y = save_dir_x * sin(0.000925 * PI) + ray_dir_y * cos(0.000925 * PI);
	}
}
