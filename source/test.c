/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:00 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/23 18:29:52 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dest;

    dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dest = color;
}

int main()
{
    t_data data;

    // Initialize MLX and create a window
    data.mlx = mlx_init();
    data.window = mlx_new_window(data.mlx, 800, 600, "Drawing Pixels");

    // Create an image
    data.image = mlx_new_image(data.mlx, 800, 600);
    data.addr = mlx_get_data_addr(data.image, &data.bits_per_pixel,
                                  &data.line_length, &data.endian);

    // Draw a red pixel at (400, 300)
    my_mlx_pixel_put(&data, 400, 300, 0x00FF0000);

    // Display the image
    mlx_put_image_to_window(data.mlx, data.window, data.image, 0, 0);

    // Start the event loop
    mlx_loop(data.mlx);

    return (0);
}
