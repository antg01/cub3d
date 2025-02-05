/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:03:39 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/05 22:56:34 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// FOV == 0.37 * PI
// start_dir = player_dir - 0.185 * PI vers la gauche, puis 10x rays de 0.037 * PI
void	draw_rays(t_mlx *data, t_player *player)
{
	float	rot_angle;
	float	ray_dir_x;
	float	ray_dir_y;

	rot_angle = 0.037 * PI;
	ray_dir_x = player->dir_x * cos(-0.185 * PI) - player->dir_y * sin(-0.185 * PI);
	ray_dir_y = player->dir_x * sin(-0.185 * PI) + player->dir_y * cos(-0.185 * PI);
}
