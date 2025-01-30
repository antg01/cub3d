/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:31 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/30 16:31:08 by gnyssens         ###   ########.fr       */
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

int	check_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != 'N')
			return (0);
		i++;
	}
	return (1);
}

int	check_if_last(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line || *line == '\0')
	{
		if (*line == '\0')
			free(line);
		return (1);
	}
	else
	{
		free(line);
		return (0);
	}
}

int	parsing(int fd, char *line)
{ //parametre *line doit etre égal à NULL !!
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || *line == '\0')
			break;
		if (0 == i && !only_ones(line))
			return(write(2, "invalid map\n", 12), 0);
		else 
		{
			if (only_ones(line))
			{
				if (!check_if_last(fd))
					return(free(line), write(2, "invalid map\n", 12), 0);
			}
			else
			{
				if (line[0] != '1' || line [ft_strlen(line) - 1] != '1')
					return(free(line), write(2, "invalid map\n", 12), 0);
				if (!check_chars(line))
					return(free(line), write(2, "invalid map\n", 12), 0);
			}
		}
		free(line);
		i++;
	}
	return (1);
}
