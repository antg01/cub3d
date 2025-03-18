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

unsigned int	str_to_hexa(char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	// Parse R
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] < '0' || str[i] > '9')
		my_exit("Error\nMissing or invalid red value");
	r = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != ',')
		my_exit("Error\nMissing first comma");
	comma_count++;
	i++;

	// Parse G
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] < '0' || str[i] > '9')
		my_exit("Error\nMissing or invalid green value");
	g = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != ',')
		my_exit("Error\nMissing second comma");
	comma_count++;
	i++;

	// Parse B
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] < '0' || str[i] > '9')
		my_exit("Error\nMissing or invalid blue value");
	b = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0' && str[i] != '\n')
		my_exit("Error\nToo many values or invalid character");

	if (comma_count != 2)
		my_exit("Error\nIncorrect comma count");

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		my_exit("Error\nColor value out of range (0-255)");

	return ((r << 16) | (g << 8) | b);
}

// void	check_colors(t_mlx *data, int fd)
// {
// 	char	*info;

// 	info = get_next_line(fd);
// 	if (!info || ft_strncmp(info, "F ", 2))
// 		my_exit("color line FLOOR");
// 	data->floor_color = str_to_hexa(info + 2);
// 	free(info);
// 	info = get_next_line(fd);
// 	if (!info || ft_strncmp(info, "C ", 2))
// 		my_exit("color line CEILING");
// 	data->ceiling_color = str_to_hexa(info + 2);
// 	free(info);
// 	skip_nl(fd);
// }
