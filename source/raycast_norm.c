/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:51:06 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 17:55:09 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_wall_height(t_raycast *r)
{
	// 7. Calculate wall height and draw start/end points
	r->line_height = (int)(WINDOW_HEIGHT / r->perp_wall_dis);
	r->draw_start = -r->line_height / 2 + WINDOW_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WINDOW_HEIGHT / 2;
	if (r->draw_end >= WINDOW_HEIGHT)
		r->draw_end = WINDOW_HEIGHT - 1;
}
