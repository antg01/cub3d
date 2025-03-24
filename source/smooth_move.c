/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:44:23 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/24 15:39:23 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_keys	*init_keys(void)
{
	t_keys	*keys;

	keys = safe_malloc(sizeof(t_keys));
	keys->backward = 0;
	keys->forward = 0;
	keys->left = 0;
	keys->right = 0;
	keys->rotate_left = 0;
	keys->rotate_right = 0;
	return (keys);
}

int	key_press(int keycode, t_mlx *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	else if (keycode == 65362 || keycode == 119)
		data->keys->forward = 1;
	else if (keycode == 65364 || keycode == 115)
		data->keys->backward = 1;
	else if (keycode == 65361 || keycode == 97)
		data->keys->rotate_left = 1;
	else if (keycode == 65363 || keycode == 100)
		data->keys->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_mlx *data)
{
	if (keycode == 65362 || keycode == 119)
		data->keys->forward = 0;
	else if (keycode == 65364 || keycode == 115)
		data->keys->backward = 0;
	else if (keycode == 65361 || keycode == 97)
		data->keys->rotate_left = 0;
	else if (keycode == 65363 || keycode == 100)
		data->keys->rotate_right = 0;
	return (0);
}

int	game_loop(t_mlx *data)
{
	t_loop	n;

	n.current_time = get_time_in_seconds();
	n.delta_time = n.current_time - data->last_frame;
	data->last_frame = n.current_time;
	n.move_speed = 4.0 * n.delta_time;
	n.rot_speed = 2.0 * n.delta_time;
	move_front_back(data, &n.new_x, &n.new_y, n.move_speed);
	n.save_dir_x = data->player->dir_x;
	n.save_plane_x = data->player->plane_x;
	rot(data, n.save_dir_x, n.save_plane_x, n.rot_speed);
	render_3d(data);
	return (0);
}
