/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:49:04 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 18:38:34 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dest;

	if (x >= 0 && x < WINDOW_LENGTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dest = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void	clear_image(t_mlx *data, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_LENGTH)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

int	handle_keypress(int keycode, t_mlx *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->window);
		free_split(data->map);
		free_all(data);
		exit(0);
	}
	return (0);
}

int	close_window(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}

void	handle_mlx(t_mlx *data)
{
	data->window = mlx_new_window(data->mlx,
			WINDOW_LENGTH, WINDOW_HEIGHT, "Top-Down View");
	data->image = mlx_new_image(data->mlx,
			WINDOW_LENGTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->image,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->player = init_player(data);
	data->keys = init_keys();
	render_3d(data);
	data->last_frame = get_time_in_seconds();
	mlx_key_hook(data->window, handle_keypress, data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 3, 1L << 1, key_release, data);
	mlx_hook(data->window, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
	free_all(data);
}
