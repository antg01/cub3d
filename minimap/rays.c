/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:03:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 15:51:20 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int rays_check_wall(t_mlx *data, int x, int y)
{
    int old_x;
    int old_y;
    int dx; //dir_x
    int dy; //dir_y

    // Vérification des limites et de la map
    if (!data || !data->map || y < 0 || x < 0 || x >= data->longest_row || y >= data->num_rows)
        return (0);
    if (!data->map[y] || data->map[y][x] == '1')
        return (0);

    old_x = (int)data->player->x_pos;
    old_y = (int)data->player->y_pos;

    // Détermination de dx
    if (data->player->dir_x > 0)
        dx = 1;
    else if (data->player->dir_x < 0)
        dx = -1;
    else
        dx = 0;

    // Détermination de dy
    if (data->player->dir_y > 0)
        dy = 1;
    else if (data->player->dir_y < 0)
        dy = -1;
    else
        dy = 0;

    // Vérification des collisions diagonales
    if (old_x != x && old_y != y)
    {
        if (dx == 1 && dy == 1 && y > 0 && x > 0)
        {
            if (data->map[y - 1] && data->map[y - 1][x] == '1' && data->map[y][x - 1] == '1')
                return (0);
        }
        else if (dx == 1 && dy == -1 && y + 1 < data->num_rows && x > 0)
        {
            if (data->map[y + 1] && data->map[y + 1][x] == '1' && data->map[y][x - 1] == '1')
                return (0);
        }
        else if (dx == -1 && dy == 1 && y > 0 && x + 1 < data->longest_row)
        {
            if (data->map[y - 1] && data->map[y - 1][x] == '1' && data->map[y][x + 1] == '1')
                return (0);
        }
        else if (dx == -1 && dy == -1 && y + 1 < data->num_rows && x + 1 < data->longest_row)
        {
            if (data->map[y + 1] && data->map[y + 1][x] == '1' && data->map[y][x + 1] == '1')
                return (0);
        }
    }

    return (1);
}


// chatGPT (pcq flemme)
void draw_long_line(t_mlx *data, double x, double y, double dir_x, double dir_y)
{
	int		cellsize;
	double	img_x;
	double	img_y;
	int		i;
	int	biggest_line;

	if (data->longest_row > data->num_rows)
		biggest_line = data->longest_row;
	else
		biggest_line = data->num_rows;
	cellsize = IMAGE_HEIGHT / biggest_line;
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

// fonction qui créé le 'sonar' du joueur, pr afficher son champ de vision dans la minimap
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
