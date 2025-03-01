/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:03:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/01 21:04:07 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// chatGPT (pcq flemme)
void draw_long_line(t_mlx *data, double x, double y, double dir_x, double dir_y)
{
	int	cellsize = IMAGE_HEIGHT / data->num_rows;
	double	img_x;
	double	img_y;

	img_x =  (x * cellsize) + 4 * dir_x; // + 4 * dir pr pas que ca cache le player blue dot
	img_y =  ((y * cellsize) + WINDOW_HEIGHT - (data->num_rows * cellsize)) + 4 * dir_y;
    while (check_wall(data, (float) (img_x / cellsize), (float) ((img_y - WINDOW_HEIGHT + (data->num_rows * cellsize)) / cellsize)))
	{
        my_mlx_pixel_put(data, (int) img_x, (int) img_y, BLUE);
        img_x += dir_x * 1.0 * cellsize; //retire le * cellsize stv des vrais rays
        img_y += dir_y * 1.0 * cellsize;
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
