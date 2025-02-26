/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:45:32 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/26 15:41:53 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_raycast(t_player *player)
{
	player->ray = safe_malloc(sizeof(t_raycast));
}

// Simple function to retrieve a pixel from the gun sprite
int get_sprite_pixel(t_img *sprite, int x, int y)
{
    char *pixel = sprite->addr
                + (y * sprite->line_length)
                + (x * (sprite->bpp / 8));
    return *(int *)pixel;
}

void draw_gun_sprite(t_mlx *data)
{
    // Where to place the gun on the screen
    int xOffset = WINDOW_LENGTH / 2 - data->hand->width / 2;
    int yOffset = WINDOW_HEIGHT - data->hand->height * 2;

    for (int y = 0; y < data->hand->height; y++)
    {
        for (int x = 0; x < data->hand->width; x++)
        {
            int color = get_sprite_pixel(data->hand, x, y);

            // If you have a "transparent color"
            // skip drawing those pixels:
            if (color != 0xFFFFFF)
            {
                my_mlx_pixel_put(data, xOffset + x, yOffset + y, color);
            }
        }
    }
}

void render_3d(t_mlx *data)
{
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
	int		color;
	double	wallX;
	
	int		z; //test for the floor

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
            if (mapX <= 0 || mapY <= 0 || mapX >= data->num_rows - 1 || mapY >= data->num_rows - 1)
				hit = 1;
			else if (data->map[mapY][mapX] == '1')
                hit = 2;
			else if (data->map[mapY][mapX] == '2')
				hit = 3;
			else if (data->map[mapY][mapX] == '3')
				hit = 4;
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
		int texture_index = 0;
		if (hit == 2)
			texture_index = 1;
		else if (hit == 3)
			texture_index = 2;
		else if (hit == 4)
			texture_index = 3;
		if (side == 0)
			wallX = data->player->y_pos + perpWallDist * rayDirY;
		else
			wallX = data->player->x_pos + perpWallDist * rayDirX;
		wallX -= floor(wallX); // keep fractional part

		int texWidth = data->textures[0].width;
		int texHeight = data->textures[0].height;
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		// [TEXTURE CODE HERE] Now draw the column using the texture
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
		z = -1; //draw ceiling
		while (++z < drawStart)
			my_mlx_pixel_put(data, x, z, SKY);
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			color = get_texture_pixel(&data->textures[texture_index], texX, texY);

			// Optional shading if horizontal side
			if (side == 1)
				color = (color >> 1) & 0x7F7F7F;

			my_mlx_pixel_put(data, x, y, color);
			z = y;
		}
		while (++z < WINDOW_HEIGHT) //draw_floor
			my_mlx_pixel_put(data, x, z, BROWN);
    }
	//draw_gun_sprite(data);
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	render(data);
}

