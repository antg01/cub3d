/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_down_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:55:19 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 19:02:59 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_biggest_line(t_mlx *data, t_grid *g, int num_rows)
{
	if (data->longest_row > num_rows)
		g->biggest_line = data->longest_row;
	else
		g->biggest_line = num_rows;
}
