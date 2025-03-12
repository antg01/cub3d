/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:09:01 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/03 16:18:26 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	which_orien(t_mlx *data, char c)
{
	if (c == 'N')
		*(data->orientation) = 'N';
	else if (c == 'S')
		*(data->orientation) = 'S';
	else if (c == 'E')
		*(data->orientation) = 'E';
	else if (c == 'W')
		*(data->orientation) = 'W';
	*(data->orientation + 1) = '\0';
}

void	check_chars(t_mlx *data, char *str, int *check_nsew, t_maplist *head)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		str[i] = '\0';

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0' &&
			str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
		{
			my_exit("Error: Non-valid character in map");
		}
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			which_orien(data, str[i]);
			(*check_nsew)++;
			printf("Player position found: %c at index %d\n", str[i], i);
		}
		if (*check_nsew > 1)
		{
			free_maplist(head);
			my_exit("Error: Too many player's start positions");
		}
		i++;
	}
}


void	check_map_walls(char **map, int rows)
{
	int	i, j;
	int	player_count = 0;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; map[i][j]; j++)
		{
			if (map[i][j] != '1' && map[i][j] != '0' &&
				map[i][j] != 'N' && map[i][j] != 'S' &&
				map[i][j] != 'E' && map[i][j] != 'W' &&
				map[i][j] != ' ')
				my_exit("Error: Invalid character in map");

			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
		}
	}

	if (player_count != 1)
		my_exit("Error: Map must contain exactly one player position");

	// Vérification des bords
	for (i = 0; i < rows; i++)
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			my_exit("Error: Map not closed on the sides");
	}
	for (j = 0; map[0][j]; j++)
		if (map[0][j] != '1')
			my_exit("Error: Map not closed at the top");
	for (j = 0; map[rows - 1][j]; j++)
		if (map[rows - 1][j] != '1')
			my_exit("Error: Map not closed at the bottom");
}

t_maplist	*extract_map(t_mlx *data, int fd, int *count_rows)
{
	char		*line;
	int			check_nsew;
	t_maplist	*head;
	t_maplist	*curr;
	t_maplist	*prev;

	head = safe_malloc(sizeof(t_maplist));
	head->line = NULL;
	head->next = NULL;
	check_nsew = 0;
	curr = head;
	prev = NULL;

	while (1)
	{
		line = get_next_line(fd);
		if (!line || '\0' == *line)
			break ;
		check_chars(data, line, &check_nsew, head);
		(*count_rows)++;
		curr->line = line;
		curr->next = safe_malloc(sizeof(t_maplist));
		curr->next->line = NULL;
		curr->next->next = NULL;
		prev = curr;
		curr = curr->next;
	}
	if (prev)
	{
		free(curr); // Supprimer le dernier élément vide inutile
		prev->next = NULL;
	}
	write(2, "EXTRACT OK\n", 11);
	return (head);
}

