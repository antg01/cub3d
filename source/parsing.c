/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:31 by gnyssens          #+#    #+#             */
/*   Updated: 2025/04/01 17:29:42 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Gère l'analyse des lignes de textures et marque les éléments déjà définis.
*/
static int	handle_texture_line(t_mlx *data, char *line, t_element_flags *flags)
{
	if (!ft_strncmp(line, "NO", 2) && !flags->no)
	{
		parse_texture_line(data, line, 0);
		flags->no = 1;
		return (1);
	}
	if (!ft_strncmp(line, "SO", 2) && !flags->so)
	{
		parse_texture_line(data, line, 1);
		flags->so = 1;
		return (1);
	}
	if (!ft_strncmp(line, "WE", 2) && !flags->we)
	{
		parse_texture_line(data, line, 2);
		flags->we = 1;
		return (1);
	}
	if (!ft_strncmp(line, "EA", 2) && !flags->ea)
	{
		parse_texture_line(data, line, 3);
		flags->ea = 1;
		return (1);
	}
	return (0);
}

/*
** Gère l'analyse des lignes de couleurs et met à jour
** les indicateurs correspondants.
*/
static int	handle_color_line(t_mlx *data, char *line, t_element_flags *flags)
{
	if (*line == 'F' && !flags->f)
	{
		parse_color_line(data, &(data->floor_color), line);
		flags->f = 1;
		return (1);
	}
	if (*line == 'C' && !flags->c)
	{
		parse_color_line(data, &(data->ceiling_color), line);
		flags->c = 1;
		return (1);
	}
	return (0);
}

/*
** Analyse une ligne de configuration et appelle le traitement approprié
**  pour textures ou couleurs.
*/
static void	handle_config_line(t_mlx *data, char *line, t_element_flags *flags)
{
	char	*trimmed_line;
	int		ok;

	trimmed_line = trim_spaces_tabs(line);
	if (*trimmed_line == '\0' || *trimmed_line == '\n')
		return ;
	ok = handle_texture_line(data, trimmed_line, flags);
	if (!ok)
		ok = handle_color_line(data, trimmed_line, flags);
	if (!ok)
		my_exit("Error: Invalid/duplicate element in config", data);
}

/*
** Lit et analyse les 6 éléments de configuration (textures et couleurs)
** depuis le fichier.
*/
static void	parse_config_elements(t_mlx *data, int fd)
{
	char			*line;
	t_element_flags	flags;
	int				count;

	init_element_flags(&flags);
	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			my_exit("Error: Unexpected EOF", data);
		handle_config_line(data, line, &flags);
		count = flags.no + flags.so + flags.we + flags.ea + flags.f + flags.c;
		free(line);
	}
}

/*
** Parse le fichier de configuration, extrait la map et
**  vérifie qu'elle est fermée.
*/
int	parsing(t_mlx *data, int fd)
{
	t_maplist	*head;
	int			count_rows;

	parse_config_elements(data, fd);
	count_rows = 0;
	head = extract_map(data, fd, &count_rows);
	if (count_rows == 0)
	{
		my_exit("Error: empty map", data);
	}
	data->num_rows = count_rows;
	data->longest_row = 0;
	data->map = make_map(head, count_rows, &(data->longest_row));
	if (!data->map)
		my_exit("make_map returned NULL (alloc or linked list issue)", data);
	check_map_closed(data, data->map, data->num_rows, data->longest_row);
	return (1);
}
