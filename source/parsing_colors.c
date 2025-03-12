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
	int				r;
	int				g;
	int				b;
	int				i;
	unsigned int	color;

	r = ft_atoi(str);
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != ',')
		my_exit("HEXA 1");
	i++;
	g = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != ',')
		my_exit("HEXA 2");
	i++;
	b = ft_atoi(str + i);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		my_exit("HEXA 3");
	color = ((r << 16) | (g << 8) | b);
	return (color);
}

void	check_colors(t_mlx *data, int fd)
{
	char	*info;
	int		floor_found = 0;
	int		ceiling_found = 0;

	for (int i = 0; i < 2; i++)
	{
		info = get_next_line(fd);
		if (!info)
			my_exit("Error: Missing floor/ceiling color");

		if (!ft_strncmp(info, "F ", 2) && !floor_found)
			floor_found = 1, data->floor_color = str_to_hexa(info + 2);
		else if (!ft_strncmp(info, "C ", 2) && !ceiling_found)
			ceiling_found = 1, data->ceiling_color = str_to_hexa(info + 2);
		else
			my_exit("Error: Invalid color format or duplicate entry");

		free(info);
	}

	if (!floor_found || !ceiling_found)
		my_exit("Error: Floor or ceiling color missing");

	skip_nl(fd);
}
