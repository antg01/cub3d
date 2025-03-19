/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:45:32 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 17:55:05 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int get_sprite_pixel(t_img *sprite, int x, int y)
{
    char *pixel = sprite->addr
                + (y * sprite->line_length)
                + (x * (sprite->bpp / 8));
    return *(int *)pixel;
}

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
		r->side_dist_x = ((r->map_x + 1) - data->player->x_pos) * r->delta_dist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (data->player->y_pos - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = ((r->map_y + 1) - data->player->y_pos) * r->delta_dist_y;
	}
	r->hit = 0;
}

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

void render_3d(t_mlx *data)
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
        // 8. Draw the vertical line for this column
		if (r.side == 0) //vertical wall
		{
			r.wall_x = data->player->y_pos + r.perp_wall_dis * r.raydir_y;
			if (r.raydir_x < 0) // west
				r.index_texture = 2;
			else
				r.index_texture = 3; //east
		}
		else //horizontal wall
		{
			r.wall_x = data->player->x_pos + r.perp_wall_dis * r.raydir_x;
			if (r.raydir_y < 0)
				r.index_texture = 0; //north
			else
				r.index_texture = 1; //south
		}
		r.wall_x -= floor(r.wall_x); // keep fractional part
		r.tex_width = data->textures[r.index_texture].width;
		r.tex_height = data->textures[r.index_texture].height;
		r.tex_x = (int)(r.wall_x * (double)r.tex_width);
		if (r.side == 0 && r.raydir_x > 0)
			r.tex_x = r.tex_width - r.tex_x - 1;
		if (r.side == 1 && r.raydir_y < 0)
			r.tex_x = r.tex_width - r.tex_x - 1;
		// [TEXTURE CODE HERE] Now draw the column using the texture
		r.step = 1.0 * r.tex_height / r.line_height;
		r.tex_pos = (r.draw_start - WINDOW_HEIGHT / 2 + r.line_height / 2) * r.step;
		r.z = -1; //draw ceiling
		while (++r.z < r.draw_start)
			my_mlx_pixel_put(data, x, r.z, data->ceiling_color);
		for (int y = r.draw_start; y < r.draw_end; y++)
		{
			r.tex_y = (int)r.tex_pos & (r.tex_height - 1);
			r.tex_pos += r.step;
			r.color = get_texture_pixel(&data->textures[r.index_texture], r.tex_x, r.tex_y);
			my_mlx_pixel_put(data, x, y, r.color);
			r.z = y;
		}
		while (++r.z < WINDOW_HEIGHT) //draw_floor
			my_mlx_pixel_put(data, x, r.z, data->floor_color);
    }
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	render(data);
}

