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
	
	check_four_dir(fd, data); //check les 4 premieres lignes, qui renseignent les textures des murs Nord/S/E/Ouest
	check_colors(data, fd);	//check et enregistre les couleurs du floor et ceiling
	count_rows = 0;
	head = extract_map(data, fd, &count_rows); //ici la map est stockée en linked list, checkée pour only '1' && '0' et max 1 'NSEW'
	data->num_rows = count_rows;
	if (0 == count_rows)
		write(2, "empty map\n", 10), exit(1);
	data->longest_row = 0;
	data->map = make_map(head, count_rows, &(data->longest_row)); //cree la map en char **

	return (1);
}
