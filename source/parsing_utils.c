/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:03:42 by angerard          #+#    #+#             */
/*   Updated: 2025/03/19 12:04:42 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*trim_spaces_tabs(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

void	parse_texture_line(t_mlx *data, char *line, int index)
{
	char	*path_copy;

	line = trim_spaces_tabs(line + 2);
	path_copy = ft_strdup(line);
	if (!path_copy)
		my_exit("Memory allocation failed in parse_texture_line");
	do_textures(data, path_copy, index);
	free(path_copy);
}

void	parse_color_line(unsigned int *color, char *line)
{
	char	*color_copy;

	line = trim_spaces_tabs(line + 1);
	color_copy = ft_strdup(line);
	if (!color_copy)
		my_exit("Memory allocation failed in parse_color_line");
	*color = str_to_hexa(color_copy);
	free(color_copy);
}

void	init_element_flags(t_element_flags *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->f = 0;
	flags->c = 0;
}
