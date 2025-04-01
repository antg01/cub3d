/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:01:45 by gnyssens          #+#    #+#             */
/*   Updated: 2025/04/01 17:30:36 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Lit une ligne et vérifie qu'elle est vide (newline), sinon affiche une erreur.
*/
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

/*
** Affiche un message d'erreur puis quitte proprement le programme.
*/

/*
** Charge une texture depuis un fichier XPM et initialise ses
** paramètres dans la structure.
*/
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
			path_texture, &width, &height);
	if (!(data->textures[index].img_ptr))
		my_exit("Error: xpm_file_to_image failed", data);
	data->textures[index].height = height;
	data->textures[index].width = width;
	data->textures[index].addr
		= mlx_get_data_addr(data->textures[index].img_ptr,
			&data->textures[index].bpp, &data->textures[index].line_length,
			&data->textures[index].endian);
}
