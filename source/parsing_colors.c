/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:56:02 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/27 17:39:25 by gnyssens         ###   ########.fr       */
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
		my_exit();
	i++;
	g = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != ',')
		my_exit();
	i++;
	b = ft_atoi(str + i);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		my_exit();
	color = ((r << 16) | (g << 8) | b);
	return (color);
}

void	check_colors(t_mlx *data, int fd)
{
	char	*info;

	info = get_next_line(fd);
	if (!info || ft_strncmp(info, "F ", 2))
		my_exit();
	data->floor_color = str_to_hexa(info);
	free(info);
	info = get_next_line(fd);
	if (!info || ft_strncmp(info, "C ", 2))
		my_exit();
	data->ceiling_color = str_to_hexa(info);
	free(info);
	skip_nl(fd);
}
