/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:44:23 by gnyssens          #+#    #+#             */
/*   Updated: 2025/04/02 17:53:21 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Initialise la structure des touches de contrôle avec des valeurs à zéro.
*/
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

/*
** Met à jour l'état des touches lors d'une pression
** clavier pour gérer les mouvements et rotations.
*/
int	key_press(int keycode, t_mlx *data)
{
	if (keycode == 65307)
	{
		free_all(data);
		exit(0);
	}
	else if (keycode == 65362 || keycode == 119)
		data->keys->forward = 1;
	else if (keycode == 65364 || keycode == 115)
		data->keys->backward = 1;
	else if (keycode == 65361)
		data->keys->rotate_left = 1;
	else if (keycode == 65363)
		data->keys->rotate_right = 1;
	else if (keycode == 97)
		data->keys->left = 1;
	else if (keycode == 100)
		data->keys->right = 1;
	return (0);
}

/*
** Réinitialise l'état des touches lorsque les touches
** de mouvement ou rotation sont relâchées.
*/
int	key_release(int keycode, t_mlx *data)
{
	if (keycode == 65362 || keycode == 119)
		data->keys->forward = 0;
	else if (keycode == 65364 || keycode == 115)
		data->keys->backward = 0;
	else if (keycode == 65361)
		data->keys->rotate_left = 0;
	else if (keycode == 65363)
		data->keys->rotate_right = 0;
	else if (keycode == 97)
		data->keys->left = 0;
	else if (keycode == 100)
		data->keys->right = 0;
	return (0);
}

void	move_left_right(t_mlx *data, double *new_x, double *new_y, double speed)
{
	if (data->keys->left)
	{
		*new_x = data->player->x_pos + data->player->dir_y * speed;
		*new_y = data->player->y_pos - data->player->dir_x * speed;
		if (check_wall(data, (int)*new_x, (int)*new_y))
		{
			data->player->x_pos = *new_x;
			data->player->y_pos = *new_y;
		}
	}
	if (data->keys->right)
	{
		*new_x = data->player->x_pos - data->player->dir_y * speed;
		*new_y = data->player->y_pos + data->player->dir_x * speed;
		if (check_wall(data, (int)*new_x, (int)*new_y))
		{
			data->player->x_pos = *new_x;
			data->player->y_pos = *new_y;
		}
	}
}

/*
** Gère la boucle principale du jeu : calcul des mouvements,
** rotations et rendu 3D.
*/
int	game_loop(t_mlx *data)
{
	t_loop	n;

	n.current_time = get_time_in_seconds();
	n.delta_time = n.current_time - data->last_frame;
	data->last_frame = n.current_time;
	n.move_speed = 4.0 * n.delta_time;
	n.rot_speed = 2.0 * n.delta_time;
	move_front_back(data, &n.new_x, &n.new_y, n.move_speed);
	move_left_right(data, &n.new_x, &n.new_y, n.move_speed);
	n.save_dir_x = data->player->dir_x;
	n.save_plane_x = data->player->plane_x;
	rot(data, n.save_dir_x, n.save_plane_x, n.rot_speed);
	render_3d(data);
	return (0);
}
