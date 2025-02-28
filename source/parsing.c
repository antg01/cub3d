/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:31 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/28 15:59:11 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parsing(t_mlx *data, int fd)
{
	t_maplist	*head;
	int			count_rows;
	
	check_four_dir(fd, data);
	check_colors(data, fd);	//apres ca, GNL arrive direct sur la map (newline deja skippee)
	count_rows = 0;
	head = extract_map(fd, &count_rows); //ici la map est stockée en linked list, checkée pour only '1' && '0' et max 1 'NSEW'
	data->num_rows = count_rows;

	return (1);
}
