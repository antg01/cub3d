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

char	*trim_spaces(char *str)
{
	int		start;
	int		end;
	char	*trimmed;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;

	trimmed = ft_substr(str, start, end - start + 1);
	return (trimmed);
}

int	is_valid_number(char *str)
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

int	count_commas(char *str)
{
	int	count = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

unsigned int	str_to_hexa(char *str)
{
	int				r, g, b;
	char			**values;
	unsigned int	color;
	char			*trimmed_value[3];

	values = ft_split(str, ',');
	if (!values || count_split(values) != 3)
	{
		free_split(values);
		my_exit("Error: Invalid RGB format. Must be R,G,B");
	}

	// Nettoyer les valeurs RGB des espaces et sauts de ligne
	trimmed_value[0] = trim_spaces(values[0]);
	trimmed_value[1] = trim_spaces(values[1]);
	trimmed_value[2] = trim_spaces(values[2]);

	if (!is_valid_number(trimmed_value[0]) || !is_valid_number(trimmed_value[1]) || !is_valid_number(trimmed_value[2]))
	{
        printf("value1: %s; value2: %s; value3: %s\n", trimmed_value[0], trimmed_value[1], trimmed_value[2]);
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

void    check_colors(t_mlx *data, int fd)
{
    char    *info;
    int     floor_found;
    int     ceiling_found;
    int     i;

    floor_found = 0;
    ceiling_found = 0;
    i = 0;

    while (i < 2)
    {
        info = get_next_line(fd);
        if (!info)
            my_exit("Error: Missing floor/ceiling color");

        if (!ft_strncmp(info, "F ", 2) && !floor_found)
        {
            if (count_commas(info + 2) != 2)
                my_exit("Error: Invalid floor color format. Expected R,G,B");
            floor_found = 1;
            data->floor_color = str_to_hexa(info + 2);
        }
        else if (!ft_strncmp(info, "C ", 2) && !ceiling_found)
        {
            if (count_commas(info + 2) != 2)
                my_exit("Error: Invalid ceiling color format. Expected R,G,B");
            ceiling_found = 1;
            data->ceiling_color = str_to_hexa(info + 2);
        }
        else
            my_exit("Error: Invalid color format or duplicate entry");

        free(info);
        i++;
    }

    if (!floor_found || !ceiling_found)
        my_exit("Error: Floor or ceiling color missing");

    skip_nl(fd);
}
