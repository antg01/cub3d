/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:52:35 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 14:26:11 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**make_map(t_maplist *head, int num_rows, int *longest_row)
{
	char		**map;
	t_maplist	*curr;
	t_maplist	*save;
	int			i;
	int			len;

	if (!head || num_rows <= 0 || !longest_row)
	{
		my_exit("Error: Invalid input to make_map");
	}

	map = safe_malloc(sizeof(char *) * (num_rows + 1));
	if (!map)
	{
		my_exit("Memory allocation failed for map");
	}

	curr = head;
	i = 0;
	while (curr && curr->line) // Sécurité : vérifie que curr et curr->line existent
	{
		map[i] = safe_strdup(curr->line);
		if (!map[i])
		{
			my_exit("Memory allocation failed for map[i]");
		}

		len = ft_strlen(map[i]);
		if (len > (*longest_row))
			*longest_row = len;

		save = curr->next;
		free(curr->line);
		curr->line = NULL;
		free(curr);
		curr = save;
		i++;
	}

	map[i] = NULL; // Ajout du NULL pour marquer la fin du tableau
	return (map);
}
