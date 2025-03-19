/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:45:32 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 17:09:07 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// cette fonction elle sert a rien pr linstant, la structure t_raycast yen aura besoin
// pr normer 'render_3d' qui a blindé de variables
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

// ici cest la grosse fonction principale du raycasting, donc pour dessiner les murs ligne verticale par ligne verticale
void render_3d(t_mlx *data)
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	double	perpWallDist;
	int		color;
	double	wallX;
	int		lineHeight;
	int		z;
	int		index_texture;
	int		hit;
	int		side;
	int		drawStart;
	int		drawEnd;
	int		texWidth;
	int		texHeight;
	int		texX;
	double	step;
	double	texPos;
	int		texY;

	for (int x = 0; x < WINDOW_LENGTH; x++) // Loop through each column
	{
		// 1. Compute the ray direction for this column
		camera_x = 2 * x / (double)WINDOW_LENGTH - 1; // camera_x in [-1, 1]
		raydir_x = data->player->dir_x + data->player->plane_x * camera_x;
		raydir_y = data->player->dir_y + data->player->plane_y * camera_x;

		// 2. Get the player's starting position in the map
		map_x = (int)data->player->x_pos; // Current grid cell X
		map_y = (int)data->player->y_pos; // Current grid cell Y

		// 3. Calculate ray step sizes
		if (raydir_x == 0)
			deltaDistX = 1000000000000;
		else
			deltaDistX = fabs(1 / raydir_x); // Distance to the next vertical grid line
		if (raydir_y == 0)
			deltaDistY = 1000000000000;
		else
			deltaDistY = fabs(1 / raydir_y); // Distance to the next horizontal grid line

		// 4. Calculate initial side distances
		if (raydir_x < 0)
		{
			stepX = -1;
			sideDistX = (data->player->x_pos - map_x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = ((map_x + 1) - data->player->x_pos) * deltaDistX;
		}

		if (raydir_y < 0)
		{
			stepY = -1;
			sideDistY = (data->player->y_pos - map_y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = ((map_y + 1) - data->player->y_pos) * deltaDistY;
		}

        // 5. Perform DDA
        hit = 0;
        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                map_x += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                map_y += stepY;
                side = 1;
            }

            // Check if the ray hit a wall
            if (map_x <= 0 || map_y <= 0)// || map_x >= data->num_rows - 1 || map_y >= data->num_rows - 1)
				hit = 1;
			else if (data->map[map_y][map_x] == '1')
				hit = 1;
        }

        // 6. Calculate distance to the wall
        if (side == 0)
    		perpWallDist = sideDistX - deltaDistX;
		else
    		perpWallDist = sideDistY - deltaDistY;

        // 7. Calculate wall height and draw start/end points
        lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
        drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawStart < 0)
			drawStart = 0;
        drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawEnd >= WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT - 1;

        // 8. Draw the vertical line for this column
		//index_texture
		if (side == 0) //vertical wall
		{
			wallX = data->player->y_pos + perpWallDist * raydir_y;
			if (raydir_x < 0) // west
				index_texture = 2;
			else
				index_texture = 3; //east
		}
		else //horizontal wall
		{
			wallX = data->player->x_pos + perpWallDist * raydir_x;
			if (raydir_y < 0)
				index_texture = 0; //north
			else
				index_texture = 1; //south
		}
		wallX -= floor(wallX); // keep fractional part

		texWidth = data->textures[index_texture].width;
		texHeight = data->textures[index_texture].height;
		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && raydir_x > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && raydir_y < 0)
			texX = texWidth - texX - 1;

		// [TEXTURE CODE HERE] Now draw the column using the texture
		step = 1.0 * texHeight / lineHeight;
		texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
		z = -1; //draw ceiling
		while (++z < drawStart)
			my_mlx_pixel_put(data, x, z, data->ceiling_color);
		for (int y = drawStart; y < drawEnd; y++)
		{
			texY = (int)texPos & (texHeight - 1);
			texPos += step;

			color = get_texture_pixel(&data->textures[index_texture], texX, texY);

			// Optional shading if horizontal side
			//if (side == 1)
			//	color = (color >> 1) & 0x7F7F7F;

			my_mlx_pixel_put(data, x, y, color);
			z = y;
		}
		while (++z < WINDOW_HEIGHT) //draw_floor
			my_mlx_pixel_put(data, x, z, data->floor_color);
    }
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	render(data);
}

