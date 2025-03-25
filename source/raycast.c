/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:45:32 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/25 18:26:45 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Récupère la couleur d'un pixel à partir des coordonnées d'une texture sprite.
*/
int	get_sprite_pixel(t_img *sprite, int x, int y)
{
	char	*pixel;

	pixel = sprite->addr + (y * sprite->line_length)
		+ (x * (sprite->bpp / 8));
	return (*(int *)pixel);
}

/*
** Initialise les variables de base pour le raycasting pour chaque colonne.
*/
void	init_variables(t_raycast *r, t_mlx *data, int x)
{
	r->camera_x = 2 * x / (double)WINDOW_LENGTH - 1;
	r->raydir_x = data->player->dir_x + data->player->plane_x * r->camera_x;
	r->raydir_y = data->player->dir_y + data->player->plane_y * r->camera_x;
	r->map_x = (int)data->player->x_pos;
	r->map_y = (int)data->player->y_pos;
	if (r->raydir_x == 0)
		r->delta_dist_x = 1000000000000;
	else
		r->delta_dist_x = fabs(1 / r->raydir_x);
	if (r->raydir_y == 0)
		r->delta_dist_y = 1000000000000;
	else
		r->delta_dist_y = fabs(1 / r->raydir_y);
}

/*
** Calcule les distances initiales du rayon jusqu'aux premières
** intersections en X et Y.
*/
void	initial_distance(t_mlx *data, t_raycast *r)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (data->player->x_pos - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = ((r->map_x + 1)
				- data->player->x_pos) * r->delta_dist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (data->player->y_pos
				- r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = ((r->map_y + 1)
				- data->player->y_pos) * r->delta_dist_y;
	}
	r->hit = 0;
}

/*
** Exécute l'algorithme DDA pour trouver le mur rencontré par le rayon
** et calcule la distance perpendiculaire.
*/
void	actual_dda(t_mlx *data, t_raycast *r)
{
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x <= 0 || r->map_y <= 0)
			r->hit = 1;
		else if (data->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perp_wall_dis = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dis = r->side_dist_y - r->delta_dist_y;
}

/*
** Effectue le rendu 3D ligne par ligne avec raycasting
** et affiche l'image finale.
*/
void	render_3d(t_mlx *data)
{
	t_raycast	r;
	int			x;

	x = -1;
	while (++x < WINDOW_LENGTH)
	{
		init_variables(&r, data, x);
		initial_distance(data, &r);
		actual_dda(data, &r);
		calc_wall_height(&r);
		prep_vertical_line(data, &r);
		r.step = 1.0 * r.tex_height / r.line_height;
		r.tex_pos = (r.draw_start - WINDOW_HEIGHT / 2
				+ r.line_height / 2) * r.step;
		r.z = -1;
		while (++r.z < r.draw_start)
			my_mlx_pixel_put(data, x, r.z, data->ceiling_color);
		draw_vertical_line(data, &r, x);
		while (++r.z < WINDOW_HEIGHT)
			my_mlx_pixel_put(data, x, r.z, data->floor_color);
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	render(data);
}
