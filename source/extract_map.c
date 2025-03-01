/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:09:01 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/01 14:35:01 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_chars(char *str, int *check_nsew)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n') //remove the '\n' for the map
		i++;
	if (str[i] == '\n')
		str[i] = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0'&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			my_exit("non-valid character in map");
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			(*check_nsew)++;
		if (*check_nsew > 1)
			my_exit("Too many player's start positions"); //would need to free the linked list
		i++;
	}
}

t_maplist	*extract_map(int fd, int *count_rows)
{
	char		*line;
	int			check_nsew; //check N S E W (max 1 per map)
	t_maplist	*head;
	t_maplist	*curr;

	head = safe_malloc(sizeof(t_maplist));
	check_nsew = 0;
	curr = head;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || '\0' == *line)
			break ;
		check_chars(line, &check_nsew);
		(*count_rows)++;
		curr->line = line;
		curr->next = safe_malloc(sizeof(t_maplist));
		curr = curr->next;
	}
	curr->line = NULL;
	curr->next = NULL;
	write(2, "EXTRACT OK\n", 11);
	return (head);
}
