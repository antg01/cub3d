/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:52:35 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/25 18:11:39 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Convertit la liste chaînée de lignes en tableau de chaînes
** et détermine la longueur maximale des lignes de la map.
*/
char	**make_map(t_maplist *head, int num_rows, int *longest_row)
{
	char		**map;
	t_maplist	*curr;
	t_maplist	*temp;
	int			i;
	int			len;

	map = safe_malloc(sizeof(char *) * (num_rows + 1));
	curr = head;
	i = 0;
	while (curr && curr->line)
	{
		map[i] = safe_strdup(curr->line);
		len = ft_strlen(map[i]);
		if (len > *longest_row)
			*longest_row = len;
		temp = curr->next;
		free(curr->line);
		free(curr);
		curr = temp;
		i++;
	}
	map[i] = NULL;
	return (map);
}
