/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:52:35 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/28 18:36:40 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**make_map(t_maplist *head, int num_rows)
{
	char		**map;
	t_maplist	*curr;
	t_maplist	*save; //to allow freeing
	int			i;

	map = safe_malloc(sizeof(char *) * (num_rows + 1));
	curr = head;
	i = 0;
	while (curr != NULL)
	{
		map[i] = safe_strdup(curr->line);
		save = curr->next;
		free(curr->line);
		curr->next = NULL;
		free(curr);
		curr = save;
		i++;
	}
	map[i] = NULL;
	return (map);
}
