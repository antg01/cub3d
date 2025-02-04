/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:49:04 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/04 15:04:43 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char    *dest;

	if (x >= 0 && x < 1000 && y >= 0 && y < 800)
	{
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void clear_image(t_mlx *data, int color)
{
    for (int y = 0; y < 800; y++)
    {
        for (int x = 0; x < 1000; x++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

int handle_keypress(int keycode, t_mlx *data)
{

    if (keycode == 65307) // Escape key (Linux)
	{
        mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	// Move left
    else if (keycode == 65361) // Left arrow
    {
		// Optionally check boundaries or collisions here
        data->player->x_pos -= 5;
    }
    // Move up
    else if (keycode == 65362) // Up arrow
    {
        data->player->y_pos -= 5;
    }
    // Move right
    else if (keycode == 65363) // Right arrow
    {
        data->player->x_pos += 5;
    }
    // Move down
    else if (keycode == 65364) // Down arrow
    {
        data->player->y_pos += 5;
    }

	render(data);
	
    return (0);
}

int close_window(t_mlx *data)
{
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

void	handle_mlx(t_mlx *data)
{
	data->mlx = mlx_init();

	data->window = mlx_new_window(data->mlx, WINDOW_LENGTH, WINDOW_HEIGHT, "Top-Down View");
	data->image = mlx_new_image(data->mlx, WINDOW_LENGTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	
	//mlx_loop_hook(data->mlx, render, data);;
	data->player = init_player(data);
	render(data);

	mlx_key_hook(data->window, handle_keypress, data);
	mlx_hook(data->window, 17, 0, close_window, data);

	mlx_loop(data->mlx);
}
