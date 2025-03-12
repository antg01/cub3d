/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:31 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 15:45:22 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parsing(t_mlx *data, int fd)
{
	t_maplist	*head;
	int			count_rows;

	if (!data || fd < 0)
	{
		my_exit("Error: Invalid input to parsing");
	}

	check_four_dir(fd, data);
	check_colors(data, fd);

	count_rows = 0;
	head = extract_map(data, fd, &count_rows);
	if (!head)
	{
		my_exit("Error: Failed to extract map");
	}

	data->num_rows = count_rows;

	if (count_rows == 0)
	{
		my_exit("Error: Empty map");
	}

	data->longest_row = 0;
	data->map = make_map(head, count_rows, &(data->longest_row));
	if (!data->map)
	{
		my_exit("Error: Failed to create map");
	}

	check_map_walls(data->map, data->num_rows);

	return (1);
}
