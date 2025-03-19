/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:01:45 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 12:07:41 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	skip_nl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (*line != '\n')
	{
		write(2, "Error: no newline\n", 18);
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
	int	height;
	int	width;
	int	i;

	i = 0;
	while (path_texture[i] && path_texture[i] != '\n')
		i++;
	if (path_texture[i] == '\n')
		path_texture[i] = '\0';
	data->textures[index].img_ptr = mlx_xpm_file_to_image(data->mlx,
															path_texture,
															&width,
															&height);
	if (!(data->textures[index].img_ptr))
		my_exit("Error: xpm_file_to_image failed");
	data->textures[index].height = height;
	data->textures[index].width = width;
	data->textures[index].addr = mlx_get_data_addr(data->textures[index].img_ptr,
													&data->textures[index].bpp,
													&data->textures[index].line_length,
													&data->textures[index].endian);
}
