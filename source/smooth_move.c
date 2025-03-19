/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:44:23 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 15:46:54 by gnyssens         ###   ########.fr       */
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

int key_press(int keycode, t_mlx *data)
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

int key_release(int keycode, t_mlx *data)
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

//fonction qui gere le fps, les mouvements fluides
int	game_loop(t_mlx *data)
{
	double newX;
	double newY;
	double currentTime;
	double deltaTime;
	double moveSpeed;
	double rot_speed;
	double	save_dir_x;
	double	save_plane_x;

	currentTime = get_time_in_seconds(); // Get time
	deltaTime = currentTime - data->last_frame;
	data->last_frame = currentTime;
	moveSpeed = 4.0 * deltaTime; // Movement speed (units per second)
	rot_speed = 2.0 * deltaTime; // Rotation speed (radians per second)

	if (data->keys->forward)
	{
		newX = data->player->x_pos + data->player->dir_x * moveSpeed;
		newY = data->player->y_pos + data->player->dir_y * moveSpeed;
		if (check_wall(data, (int)newX, (int)newY))
		{
			data->player->x_pos = newX;
			data->player->y_pos = newY;
		}
	}
	if (data->keys->backward)
	{
		newX = data->player->x_pos - data->player->dir_x * moveSpeed;
		newY = data->player->y_pos - data->player->dir_y * moveSpeed;
		if (check_wall(data, (int)newX, (int)newY))
		{
			data->player->x_pos = newX;
			data->player->y_pos = newY;
		}
	}

	save_dir_x = data->player->dir_x;
	save_plane_x = data->player->plane_x;
	if (data->keys->rotate_left)
	{
		data->player->dir_x = data->player->dir_x * cos(-rot_speed) - data->player->dir_y * sin(-rot_speed);
		data->player->dir_y = save_dir_x * sin(-rot_speed) + data->player->dir_y * cos(-rot_speed);

		data->player->plane_x = data->player->plane_x * cos(-rot_speed) - data->player->plane_y * sin(-rot_speed);
		data->player->plane_y = save_plane_x * sin(-rot_speed) + data->player->plane_y * cos(-rot_speed);
	}
	if (data->keys->rotate_right)
	{
		data->player->dir_x = data->player->dir_x * cos(rot_speed) - data->player->dir_y * sin(rot_speed);
		data->player->dir_y = save_dir_x * sin(rot_speed) + data->player->dir_y * cos(rot_speed);

		data->player->plane_x = data->player->plane_x * cos(rot_speed) - data->player->plane_y * sin(rot_speed);
		data->player->plane_y = save_plane_x * sin(rot_speed) + data->player->plane_y * cos(rot_speed);
	}

	//clear_image(data, 0X000000);
	render_3d(data);

	return (0);
}
