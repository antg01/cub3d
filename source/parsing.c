/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:31 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/30 15:51:03 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	only_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

char	**parsing(int fd)
{
	int		i;
	int		row_len;
	int		col_len;
	char	*line;
	char	**result;

	line = NULL;
	i = 0;
	while (line != NULL || i == 0)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		if (0 == i)
		{
			row_len = ft_strlen(line);
			if (!only_ones(line))
				return(write(2, "invalid map\n", 12), NULL);
		}
		else 
		{
			if (line[0] != '1' || line [ft_strlen(line) - 1] != '1')
				return(write(2, "invalid map\n", 12), NULL);
		}
		
	}
}
