/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:49:04 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/31 16:36:17 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char    *dest;

	if (x >= 0 && x < 800 && y >= 0 && y < 600)
	{
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void clear_image(t_mlx *data, int color)
{
    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 800; x++)
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
	data->window = mlx_new_window(data->mlx, 1200, 1200, "Top-Down View");

	mlx_key_hook(data->window, handle_keypress, data);
	mlx_hook(data->window, 17, 0, close_window, data);

	mlx_loop(data->mlx);
}
