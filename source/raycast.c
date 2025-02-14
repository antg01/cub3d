/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:45:32 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/14 01:47:16 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_raycast(t_player *player)
{
	player->ray = safe_malloc(sizeof(t_raycast));
}

void render_3d(t_mlx *data)
{
    //int cellsize = WINDOW_LENGTH / data->num_rows; // Pixels per grid cell

	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int 	mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	double	perpWallDist;

    for (int x = 0; x < WINDOW_LENGTH; x++) // Loop through each column
    {
        // 1. Compute the ray direction for this column
        cameraX = 2 * x / (double)WINDOW_LENGTH - 1; // cameraX in [-1, 1]
        rayDirX = data->player->dir_x + data->player->plane_x * cameraX;
        rayDirY = data->player->dir_y + data->player->plane_y * cameraX;

        // 2. Get the player's starting position in the map
        mapX = (int)data->player->x_pos; // Current grid cell X
        mapY = (int)data->player->y_pos; // Current grid cell Y

        // 3. Calculate ray step sizes
		if (rayDirX == 0)
			deltaDistX = 1000000000000;
		else
        	deltaDistX = fabs(1 / rayDirX); // Distance to the next vertical grid line
		if (rayDirY == 0)
			deltaDistY = 1000000000000;
		else
        	deltaDistY = fabs(1 / rayDirY); // Distance to the next horizontal grid line

        // 4. Calculate initial side distances
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->player->x_pos - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = ((mapX + 1) - data->player->x_pos) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->player->y_pos - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = ((mapY + 1) - data->player->y_pos) * deltaDistY;
        }

        // 5. Perform DDA
        int hit = 0; // Wall hit flag
        int side;    // Was the wall hit a vertical or horizontal one?
        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Check if the ray hit a wall
            if (data->map[mapY][mapX] == '1')
                hit = 1;
        }

        // 6. Calculate distance to the wall
        if (side == 0)
    		perpWallDist = sideDistX - deltaDistX;
		else
    		perpWallDist = sideDistY - deltaDistY;

        // 7. Calculate wall height and draw start/end points
        int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawStart < 0)
			drawStart = 0;
        int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawEnd >= WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT - 1;

        // 8. Draw the vertical line for this column
        int color = (side == 0) ? 0xFF0000 : 0x880000; // Red walls, darker if horizontal
        for (int y = drawStart; y < drawEnd; y++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }

    // Push the image to the window
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

