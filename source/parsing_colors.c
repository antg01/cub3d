/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:56:02 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/01 14:26:49 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char *trim_spaces(char *str)
{
    int start;
    int end;
    char *trimmed;

    if (!str)
        return (NULL);
    start = 0;
    while (str[start] && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n'))
        start++;
    end = ft_strlen(str) - 1;
    while (end > start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
        end--;

    trimmed = ft_substr(str, start, end - start + 1);
    return (trimmed);
}

int is_valid_number(char *str)
{
    int i = 0;

    if (!str || !str[0])
        return (0);
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int	count_split(char **split)
{
	int	count = 0;

	while (split[count])
		count++;
	return (count);
}

unsigned int str_to_hexa(char *str)
{
    int r, g, b;
    char **values;
    unsigned int color;
    char *trimmed_value[3];

    char *trimmed_str = trim_spaces(str);
    values = ft_split(trimmed_str, ',');
    free(trimmed_str);
    if (!values || count_split(values) != 3)
    {
        free_split(values);
        my_exit("Error: Invalid RGB format. Must be R,G,B");
    }

    trimmed_value[0] = trim_spaces(values[0]);
    trimmed_value[1] = trim_spaces(values[1]);
    trimmed_value[2] = trim_spaces(values[2]);

    if (!is_valid_number(trimmed_value[0]) || !is_valid_number(trimmed_value[1]) || !is_valid_number(trimmed_value[2]))
    {
        free_split(values);
        free(trimmed_value[0]);
        free(trimmed_value[1]);
        free(trimmed_value[2]);
        my_exit("Error: RGB values must be numbers between 0 and 255");
    }

    r = ft_atoi(trimmed_value[0]);
    g = ft_atoi(trimmed_value[1]);
    b = ft_atoi(trimmed_value[2]);

    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
    {
        free_split(values);
        free(trimmed_value[0]);
        free(trimmed_value[1]);
        free(trimmed_value[2]);
        my_exit("Error: RGB values must be between 0 and 255");
    }

    color = ((r << 16) | (g << 8) | b);
    free_split(values);
    free(trimmed_value[0]);
    free(trimmed_value[1]);
    free(trimmed_value[2]);

    return (color);
}

// void check_colors(t_mlx *data, int fd)
// {
//     char *info;
//     char *trimmed;
//     int floor_found;
//     int ceiling_found;
//     int i;

//     floor_found = 0;
//     ceiling_found = 0;
//     i = 0;

//     while (i < 2)
//     {
//         info = get_next_line(fd);
//         while (info && *trim_spaces(info) == '\0') // Skip empty lines
//         {
//             free(info);
//             info = get_next_line(fd);
//         }

//         if (!info)
//             my_exit("Error: Missing floor/ceiling color");

//         trimmed = trim_spaces(info);

//         if (!ft_strncmp(trimmed, "F ", 2) && !floor_found)
//         {
//             floor_found = 1;
//             data->floor_color = str_to_hexa(trim_spaces(trimmed + 2));
//         }
//         else if (!ft_strncmp(trimmed, "C ", 2) && !ceiling_found)
//         {
//             ceiling_found = 1;
//             data->ceiling_color = str_to_hexa(trim_spaces(trimmed + 2));
//         }
//         else
//             my_exit("Error: Invalid color format or duplicate entry");

//         free(info);
//         free(trimmed);
//         i = i + 1;
//     }

//     if (!floor_found || !ceiling_found)
//         my_exit("Error: Floor or ceiling color missing");
// }

