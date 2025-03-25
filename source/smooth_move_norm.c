/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_move_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:22:33 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/25 18:25:45 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Gère les déplacements avant et arrière du joueur en vérifiant les collisions.
*/
void	move_front_back(t_mlx *data, double *new_x, double *new_y, double speed)
{
	if (data->keys->forward)
	{
		*new_x = data->player->x_pos + data->player->dir_x * speed;
		*new_y = data->player->y_pos + data->player->dir_y * speed;
		if (check_wall(data, (int)*new_x, (int)*new_y))
		{
			data->player->x_pos = *new_x;
			data->player->y_pos = *new_y;
		}
	}
	if (data->keys->backward)
	{
		*new_x = data->player->x_pos - data->player->dir_x * speed;
		*new_y = data->player->y_pos - data->player->dir_y * speed;
		if (check_wall(data, (int)*new_x, (int)*new_y))
		{
			data->player->x_pos = *new_x;
			data->player->y_pos = *new_y;
		}
	}
}

/*
** Applique la rotation du joueur et du plan de caméra
** selon les touches de rotation.
*/
void	rot(t_mlx *data, double save_dir_x, double save_plane, double rot_speed)
{
	if (data->keys->rotate_left)
	{
		data->player->dir_x = data->player->dir_x
			* cos(-rot_speed) - data->player->dir_y * sin(-rot_speed);
		data->player->dir_y = save_dir_x
			* sin(-rot_speed) + data->player->dir_y * cos(-rot_speed);
		data->player->plane_x = data->player->plane_x
			* cos(-rot_speed) - data->player->plane_y * sin(-rot_speed);
		data->player->plane_y = save_plane
			* sin(-rot_speed) + data->player->plane_y * cos(-rot_speed);
	}
	if (data->keys->rotate_right)
	{
		data->player->dir_x = data->player->dir_x
			* cos(rot_speed) - data->player->dir_y * sin(rot_speed);
		data->player->dir_y = save_dir_x * sin(rot_speed)
			+ data->player->dir_y * cos(rot_speed);
		data->player->plane_x = data->player->plane_x
			* cos(rot_speed) - data->player->plane_y * sin(rot_speed);
		data->player->plane_y = save_plane
			* sin(rot_speed) + data->player->plane_y * cos(rot_speed);
	}
}
