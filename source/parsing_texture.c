/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:01:45 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/01 14:28:12 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	skip_nl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (*line != '\n')
	{
		write(2, "Error, no newline\n", 18);
		exit(EXIT_FAILURE);
	}
	free(line);
}

void	my_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_SUCCESS);
}

void	do_textures(t_mlx *data, char *path_texture, int index)
{
	int		height;
	int		width;
	int		i;

	i = 0;
	while (path_texture[i] && path_texture[i] != '\n')
		i++;
	if (path_texture[i] == '\n')
		path_texture[i] = '\0';
	data->textures[index].img_ptr = mlx_xpm_file_to_image(data->mlx, path_texture,
		&width, &height);
	if (!(data->textures[index].img_ptr))
		my_exit("xpm_file_to_image failed");
	data->textures[index].height = height;
	data->textures[index].width = width;
	data->textures[index].addr = mlx_get_data_addr(data->textures[index].img_ptr,
		&data->textures[index].bpp, &data->textures[index].line_length, &data->textures[index].endian);
}

void	check_four_dir(int fd, t_mlx *data)
{
	char	*current;
	char	*path;
	int		found[4] = {0}; // Pour suivre si chaque texture a été trouvée

	for (int i = 0; i < 4; i++)
	{
		current = get_next_line(fd);
		if (!current)
			my_exit("Error: Missing texture line");

		if (!ft_strncmp(current, "NO ", 3) && !found[0])
			found[0] = 1, path = current + 3, do_textures(data, path, 0);
		else if (!ft_strncmp(current, "SO ", 3) && !found[1])
			found[1] = 1, path = current + 3, do_textures(data, path, 1);
		else if (!ft_strncmp(current, "WE ", 3) && !found[2])
			found[2] = 1, path = current + 3, do_textures(data, path, 2);
		else if (!ft_strncmp(current, "EA ", 3) && !found[3])
			found[3] = 1, path = current + 3, do_textures(data, path, 3);
		else
			my_exit("Error: Invalid texture format or duplicate entry");

		free(current);
	}

	// Vérifier que toutes les textures ont été trouvées
	if (!found[0] || !found[1] || !found[2] || !found[3])
		my_exit("Error: Missing one or more textures");

	skip_nl(fd);
}

