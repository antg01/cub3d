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

void parse_textures_and_colors(int fd, t_mlx *data)
{
    char *line;
    char *trimmed;
    int found_textures[4] = {0}; // NO, SO, WE, EA
    int floor_found = 0;
    int ceiling_found = 0;

    while ((line = get_next_line(fd)))
    {
        trimmed = trim_spaces(line);
        if (!*trimmed) // Ignorer les lignes vides
        {
            free(line);
            free(trimmed);
            continue;
        }

        if (trimmed[0] == '1' || trimmed[0] == '0') // Début de la map
        {
            free(line);
            free(trimmed);
            return; // Sortir dès qu'on trouve la map
        }

        if (!ft_strncmp(trimmed, "NO ", 3) && !found_textures[0])
        {
            found_textures[0] = 1;
            do_textures(data, trim_spaces(trimmed + 3), 0);
        }
        else if (!ft_strncmp(trimmed, "SO ", 3) && !found_textures[1])
        {
            found_textures[1] = 1;
            do_textures(data, trim_spaces(trimmed + 3), 1);
        }
        else if (!ft_strncmp(trimmed, "WE ", 3) && !found_textures[2])
        {
            found_textures[2] = 1;
            do_textures(data, trim_spaces(trimmed + 3), 2);
        }
        else if (!ft_strncmp(trimmed, "EA ", 3) && !found_textures[3])
        {
            found_textures[3] = 1;
            do_textures(data, trim_spaces(trimmed + 3), 3);
        }
        else if (!ft_strncmp(trimmed, "F ", 2) && !floor_found)
        {
            floor_found = 1;
            data->floor_color = str_to_hexa(trim_spaces(trimmed + 2));
        }
        else if (!ft_strncmp(trimmed, "C ", 2) && !ceiling_found)
        {
            ceiling_found = 1;
            data->ceiling_color = str_to_hexa(trim_spaces(trimmed + 2));
        }
        else
            my_exit("Error: Invalid or duplicate entry in texture/color section");

        free(line);
        free(trimmed);
    }

    if (!found_textures[0] || !found_textures[1] || !found_textures[2] || !found_textures[3])
        my_exit("Error: Missing one or more textures");
    if (!floor_found || !ceiling_found)
        my_exit("Error: Floor or ceiling color missing");
}

int parsing(t_mlx *data, int fd)
{
    t_maplist *head;
    int count_rows;
    char *line;
    char *trimmed;

    if (!data || fd < 0)
        my_exit("Error: Invalid input to parsing");

    parse_textures_and_colors(fd, data);
    printf("parse ok\n");

    // Fermer et rouvrir le fichier pour repartir du début
    close(fd);
    fd = open("maps/test.cub", O_RDONLY);
    if (fd < 0)
        my_exit("Error: Failed to reopen map file");

    // Ignorer les textures et couleurs et récupérer la première ligne de map
    count_rows = 0;
    head = NULL;
    while ((line = get_next_line(fd)))
    {
        trimmed = trim_spaces(line);
        if (trimmed[0] == '1' || trimmed[0] == '0')
        {
            // On passe la ligne détectée directement à extract_map
            head = extract_map(data, fd, &count_rows, line, trimmed);
            break;
        }
        free(line);
        free(trimmed);
    }

    close(fd);

    if (!head)
        my_exit("Error: Failed to extract map");

    data->num_rows = count_rows;
    if (count_rows == 0)
        my_exit("Error: Empty map");

    data->longest_row = 0;
    data->map = make_map(head, count_rows, &(data->longest_row));
    if (!data->map)
        my_exit("Error: Failed to create map");

    check_map_walls(data->map, data->num_rows);
    return (1);
}

