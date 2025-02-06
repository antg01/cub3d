/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:03:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/06 16:10:08 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// chatGPT (pcq flemme)
void draw_long_line(t_mlx *data, int pos_x, int pos_y, double dir_x, double dir_y)
{
	int	cellsize = IMAGE_HEIGHT / 10;
    // Start at the given position, using double precision for smooth stepping.
    double x = pos_x;
    double y = pos_y;
    
    // Define a step size in pixels.
    // A step of 1.0 means we move approximately 1 pixel per iteration along the ray.
    double step = 1.0;
    
    // Loop until the ray goes out of the window boundaries.
    // (Adjust WINDOW_LENGTH and WINDOW_HEIGHT to your window's dimensions.)
    while (x >= 4 * cellsize && x < 13 * cellsize && y >= 2 * cellsize && y < 11 * cellsize) // cellsize et num_rows hardcodée ici
    {
        // Use your check_wall function (which you must implement)
        // to see if the current position (cast to int) is inside a wall.
        if (!check_wall(data, (float)x, (float)y))
            break;

        // Draw the current pixel in the given color.
        my_mlx_pixel_put(data, (int)x, (int)y, 0x00FF00);

        // Advance the ray in the direction of (dir_x, dir_y).
        // For example, if dir_x == 0.6 and dir_y == 0.8, then x increases by 0.6 and y by 0.8 each step.
        x += dir_x * step;
        y += dir_y * step;
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
	while (i <= 20)
	{
		draw_long_line(data, (int)player->x_pos, (int)player->y_pos, ray_dir_x, ray_dir_y);
		i++;
		save_dir_x = ray_dir_x;
		ray_dir_x = ray_dir_x * cos(0.0185 * PI) - ray_dir_y * sin(0.0185 * PI);
		ray_dir_y = save_dir_x * sin(0.0185 * PI) + ray_dir_y * cos(0.0185 * PI);
	}
}
