/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:51:06 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 18:14:11 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_wall_height(t_raycast *r)
{
	r->line_height = (int)(WINDOW_HEIGHT / r->perp_wall_dis);
	r->draw_start = -r->line_height / 2 + WINDOW_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WINDOW_HEIGHT / 2;
	if (r->draw_end >= WINDOW_HEIGHT)
		r->draw_end = WINDOW_HEIGHT - 1;
}

void	prep_vertical_line(t_mlx *data, t_raycast *r)
{
	if (r->side == 0)
	{
		r->wall_x = data->player->y_pos + r->perp_wall_dis * r->raydir_y;
		if (r->raydir_x < 0)
			r->index_texture = 2;
		else
			r->index_texture = 3;
	}
	else
	{
		r->wall_x = data->player->x_pos + r->perp_wall_dis * r->raydir_x;
		if (r->raydir_y < 0)
			r->index_texture = 0;
		else
			r->index_texture = 1;
	}
	r->wall_x -= floor(r->wall_x);
	r->tex_width = data->textures[r->index_texture].width;
	r->tex_height = data->textures[r->index_texture].height;
	r->tex_x = (int)(r->wall_x * (double)r->tex_width);
	if (r->side == 0 && r->raydir_x > 0)
		r->tex_x = r->tex_width - r->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		r->tex_x = r->tex_width - r->tex_x - 1;
}

void	draw_vertical_line(t_mlx *data, t_raycast *r, int x)
{
	int	y;

	y = r->draw_start - 1;
	while (++y < r->draw_end)
	{
		r->tex_y = (int)r->tex_pos & (r->tex_height - 1);
		r->tex_pos += r->step;
		r->color = get_texture_pixel(&data->textures[r->index_texture],
				r->tex_x, r->tex_y);
		my_mlx_pixel_put(data, x, y, r->color);
		r->z = y;
	}
}
