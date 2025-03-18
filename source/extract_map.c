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

void check_map_closed(char **map, int num_rows, int longest_row)
{
    int i;
    int j;

    i = 0;
    while (i < num_rows)
    {
        j = 0;
        while (j < longest_row && map[i][j])
        {
            if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                if (i == 0 || j == 0 || i == num_rows - 1 || j == longest_row - 1)
                    my_exit("Map is not closed (border)");
                if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
                    my_exit("Map is not closed (adjacent to space)");
            }
            j++;
        }
        i++;
    }
}

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

void	check_chars(t_mlx *data, char *str, int *check_nsew)
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
		{
			which_orien(data, str[i]);
			(*check_nsew)++;
		}
		if (*check_nsew > 1)
			my_exit("Too many player's start positions"); //would need to free the linked list
		i++;
	}
}

t_maplist *extract_map(t_mlx *data, int fd, int *count_rows)
{
    char        *line;
    int          check_nsew;
    t_maplist   *head;
    t_maplist   *curr;

    check_nsew = 0;
    head = NULL;
    curr = NULL;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        char *trimmed_line = trim_spaces_tabs(line);
        if (*trimmed_line == '\0' || *trimmed_line == '\n')
        {
            free(line);
            continue;
        }

        check_chars(data, trimmed_line, &check_nsew);

        if (!head)
        {
            head = safe_malloc(sizeof(t_maplist));
            curr = head;
        }
        else
        {
            curr->next = safe_malloc(sizeof(t_maplist));
            curr = curr->next;
        }

        curr->line = ft_strdup(trimmed_line);
        curr->next = NULL;
        free(line);
        (*count_rows)++;
    }

    if (check_nsew == 0)
        my_exit("No player start position found in map");

    if (!head)
        my_exit("extract_map: head is NULL (no lines read)");
    write(2, "EXTRACT OK\n", 11);
    return (head);
}
