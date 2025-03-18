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

char	*replace_spaces_with_walls(char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = safe_strdup(line);
	while (new_line[i])
	{
		if (new_line[i] == ' ' || new_line[i] == '\t')
			new_line[i] = '1';
		i++;
	}
	return (new_line);
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

void check_chars(t_mlx *data, char *str, int *check_nsew, t_maplist *head)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        str[i] = '\0';

    printf("Checking line: '%s'\n", str); // Debug: Affiche la ligne complète

    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '1' && str[i] != '0' &&
            str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
        {
            printf("Invalid character found: '%c' (ASCII: %d) at index %d\n", str[i], str[i], i);
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

void    check_map_walls(char **map, int rows)
{
    int i;
    int j;
    int player_count = 0;

    // Vérification ligne du haut
    j = 0;
    while (map[0][j])
    {
        if (map[0][j] != '1' && map[0][j] != ' ')
            my_exit("Error: Map not closed at the top");
        j++;
    }

    // Vérification ligne du bas
    j = 0;
    while (map[rows - 1][j])
    {
        if (map[rows - 1][j] != '1' && map[rows - 1][j] != ' ')
            my_exit("Error: Map not closed at the bottom");
        j++;
    }

    // Vérification des lignes intermédiaires
    i = 1;
    while (i < rows - 1)
    {
        j = 0;

        // Ignorer espaces à gauche
        while (map[i][j] == ' ')
            j++;
        if (map[i][j] != '1')
            my_exit("Error: Map not closed on the left side");

        // Vérifier chaque caractère
        while (map[i][j])
        {
            if (map[i][j] != '1' && map[i][j] != '0' &&
                map[i][j] != 'N' && map[i][j] != 'S' &&
                map[i][j] != 'E' && map[i][j] != 'W' &&
                map[i][j] != ' ')
                my_exit("Error: Invalid character in map");

            if (map[i][j] == 'N' || map[i][j] == 'S' ||
                map[i][j] == 'E' || map[i][j] == 'W')
                player_count++;
            j++;
        }

        // Vérifier côté droit
        j--;
        while (j >= 0 && map[i][j] == ' ')
            j--;
        if (j < 0 || map[i][j] != '1')
            my_exit("Error: Map not closed on the right side");

        i++;
    }

    if (player_count != 1)
        my_exit("Error: Map must contain exactly one player position");
}

t_maplist *extract_map(t_mlx *data, int fd, int *count_rows, char *first_line, char *first_trimmed)
{
    char *line;
    char *line_to_store;
    int check_nsew;
    t_maplist *head;
    t_maplist *curr;
    t_maplist *prev;

    head = safe_malloc(sizeof(t_maplist));
    head->line = NULL;
    head->next = NULL;
    curr = head;
    prev = NULL;
    check_nsew = 0;

    // Ajout de la première ligne détectée
    check_chars(data, first_trimmed, &check_nsew, head);
    (*count_rows)++;
    line_to_store = replace_spaces_with_walls(first_trimmed);
    curr->line = safe_strdup(line_to_store);
    free(line_to_store);
    curr->next = safe_malloc(sizeof(t_maplist));
    curr->next->line = NULL;
    curr->next->next = NULL;
    prev = curr;
    curr = curr->next;
    free(first_line);
    free(first_trimmed);

    // Lecture des lignes suivantes
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;

        char *trimmed = trim_spaces(line);
        if (!*trimmed || (!ft_strchr("10", trimmed[0]) && trimmed[0] != ' '))
        {
            free(line);
            free(trimmed);
            continue;
        }

        check_chars(data, trimmed, &check_nsew, head);
        (*count_rows)++;

        line_to_store = replace_spaces_with_walls(trimmed);
        curr->line = safe_strdup(line_to_store);
        free(line_to_store);
        curr->next = safe_malloc(sizeof(t_maplist));
        curr->next->line = NULL;
        curr->next->next = NULL;
        prev = curr;
        curr = curr->next;

        free(line);
        free(trimmed);
    }

    if (prev)
    {
        free(curr);
        prev->next = NULL;
    }
    write(2, "EXTRACT OK\n", 11);
    return head;
}
