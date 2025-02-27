/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:01:45 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/27 16:47:20 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	skip_nl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (*line != '\0')
	{
		write(2, "Error, no newline\n", 18);
		exit(EXIT_FAILURE);
	}
	free(line);
}

void	my_exit(void)
{
	write(2, "Error, info file corrupted\n", 27);
	exit(EXIT_SUCCESS);
}

void	do_textures(t_mlx *data, char *path_texture, int index)
{
	int	height;
	int	width;

	data->textures[index].img_ptr = mlx_xpm_file_to_image(data->mlx, path_texture,
		&width, &height);
	if (!(data->textures[index].img_ptr))
		my_exit();
	data->textures[index].height = height;
	data->textures[index].width = width;
	data->textures[index].addr = mlx_get_data_addr(data->textures[0].img_ptr,
		&data->textures[0].bpp, &data->textures[0].line_length, &data->textures[0].endian);
}

void	check_four_dir(int fd, t_mlx *data)
{
	int		i;
	char	*current;
	char	*path;

	i = 0;
	while (i < 4)
	{
		current = get_next_line(fd);
		if (i == 0)
			if (!current || ft_strncmp(current, "NO ./", 5))
				my_exit();
		else if (i == 1)
			if (!current || ft_strncmp(current, "SO ./", 5))
				my_exit();
		else if (i == 2)
			if (!current || ft_strncmp(current, "WE ./", 5))
				my_exit();
		else if (i == 3)
			if (!current || ft_strncmp(current, "EA ./", 5))
				my_exit();
		path = current + 5;
		do_textures(data, path, i);
		free(current);
	}
	skip_nl(fd);
}
