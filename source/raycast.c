/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:45:32 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/12 16:38:09 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_raycast(t_player *player)
{
	player->ray = safe_malloc(sizeof(t_raycast));
}

void render_3d(t_mlx *data)
{
    int cellsize = WINDOW_LENGTH / data->num_rows; // Pixels per grid cell

    for (int x = 0; x < WINDOW_LENGTH; x++) // Loop through each column
    {
        // 1. Compute the ray direction for this column
        double cameraX = 2 * x / (double)WINDOW_LENGTH - 1; // cameraX in [-1, 1]
        double rayDirX = data->player->dir_x + data->player->plane_x * cameraX;
        double rayDirY = data->player->dir_y + data->player->plane_y * cameraX;

        // 2. Get the player's starting position in the map
        int mapX = (int)(data->player->x_pos / cellsize); // Current grid cell X
        int mapY = (int)(data->player->y_pos / cellsize); // Current grid cell Y

        // 3. Calculate ray step sizes
        double deltaDistX = fabs(1 / rayDirX); // Distance to the next vertical grid line
        double deltaDistY = fabs(1 / rayDirY); // Distance to the next horizontal grid line

        // 4. Calculate initial side distances
        double sideDistX, sideDistY;
        int stepX, stepY;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->player->x_pos - mapX * cellsize) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = ((mapX + 1) * cellsize - data->player->x_pos) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->player->y_pos - mapY * cellsize) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = ((mapY + 1) * cellsize - data->player->y_pos) * deltaDistY;
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
            if (mapX >= 0 && mapX < data->num_rows &&
                mapY >= 0 && mapY < data->num_rows &&
                data->map[mapY][mapX] == '1')
            {
                hit = 1;
            }
        }

        // 6. Calculate distance to the wall
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX * cellsize - data->player->x_pos + (1 - stepX) * cellsize / 2) / rayDirX;
        else
            perpWallDist = (mapY * cellsize - data->player->y_pos + (1 - stepY) * cellsize / 2) / rayDirY;

        // 7. Calculate wall height and draw start/end points
        int lineHeight = (int)(WINDOW_HEIGHT * 50 / perpWallDist);
        int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawEnd >= WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT - 1;

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

