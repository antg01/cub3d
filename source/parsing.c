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

char *trim_spaces_tabs(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}

void parse_texture_line(t_mlx *data, char *line, int index)
{
    char *path_copy;

    line = trim_spaces_tabs(line + 2);
    path_copy = ft_strdup(line);
    if (!path_copy)
        my_exit("Memory allocation failed in parse_texture_line");
    do_textures(data, path_copy, index);
    free(path_copy);
}

void parse_color_line(unsigned int *color, char *line)
{
    char *color_copy;

    line = trim_spaces_tabs(line + 1);
    color_copy = ft_strdup(line);
    if (!color_copy)
        my_exit("Memory allocation failed in parse_color_line");
    *color = str_to_hexa(color_copy);
    free(color_copy);
}

void parse_config_elements(t_mlx *data, int fd)
{
    char *line;
    char *trimmed_line;
    int no_found = 0;
    int so_found = 0;
    int we_found = 0;
    int ea_found = 0;
    int f_found = 0;
    int c_found = 0;

    while (no_found + so_found + we_found + ea_found + f_found + c_found < 6)
    {
        line = get_next_line(fd);
        if (!line)
            my_exit("Error: Unexpected EOF before all elements parsed");

        trimmed_line = trim_spaces_tabs(line);
        if (*trimmed_line == '\0' || *trimmed_line == '\n')
        {
            free(line);
            continue;
        }
        if (!ft_strncmp(trimmed_line, "NO", 2) && !no_found)
        {
            parse_texture_line(data, trimmed_line, 0);
            no_found = 1;
        }
        else if (!ft_strncmp(trimmed_line, "SO", 2) && !so_found)
        {
            parse_texture_line(data, trimmed_line, 1);
            so_found = 1;
        }
        else if (!ft_strncmp(trimmed_line, "WE", 2) && !we_found)
        {
            parse_texture_line(data, trimmed_line, 2);
            we_found = 1;
        }
        else if (!ft_strncmp(trimmed_line, "EA", 2) && !ea_found)
        {
            parse_texture_line(data, trimmed_line, 3);
            ea_found = 1;
        }
        else if (*trimmed_line == 'F' && !f_found)
        {
            parse_color_line(&(data->floor_color), trimmed_line);
            f_found = 1;
        }
        else if (*trimmed_line == 'C' && !c_found)
        {
            parse_color_line(&(data->ceiling_color), trimmed_line);
            c_found = 1;
        }
        else
            my_exit("Error: Invalid or duplicate element in config");

        free(line);
    }
}


int parsing(t_mlx *data, int fd)
{
    t_maplist   *head;
    int          count_rows;

    parse_config_elements(data, fd); // parse textures and colors in any order with spaces and tabs

    count_rows = 0;
    head = extract_map(data, fd, &count_rows);

    if (count_rows == 0)
    {
        my_exit("Error: empty map");
    }

    data->num_rows = count_rows;
    data->longest_row = 0;
    data->map = make_map(head, count_rows, &(data->longest_row));

    if (!data->map)
        my_exit("make_map returned NULL (allocation or linked list issue)");

    check_map_closed(data->map, data->num_rows, data->longest_row); // ensure map is closed

    return (1);
}
