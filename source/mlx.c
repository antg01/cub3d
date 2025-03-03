/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:49:04 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/03 16:25:58 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char    *dest;

	if (x >= 0 && x < WINDOW_LENGTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void clear_image(t_mlx *data, int color)
{
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_LENGTH; x++)
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
		free_split(data->map);
		//free reste aussi
		exit(0);
	}

	return (0);
}

int close_window(t_mlx *data)
{
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

void	handle_mlx(t_mlx *data)
{
	data->window = mlx_new_window(data->mlx, WINDOW_LENGTH, WINDOW_HEIGHT, "Top-Down View");
	data->image = mlx_new_image(data->mlx, WINDOW_LENGTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	
	data->player = init_player(data);
	data->keys = init_keys();
	init_raycast(data->player);
	render_3d(data);

	data->last_frame = get_time_in_seconds();
	mlx_key_hook(data->window, handle_keypress, data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);    // Key press
	mlx_hook(data->window, 3, 1L << 1, key_release, data);  // Key release
	mlx_hook(data->window, 17, 0, close_window, data);

	mlx_loop_hook(data->mlx, game_loop, data); // Game loop for smooth movement

	mlx_loop(data->mlx);
}
